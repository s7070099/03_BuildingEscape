// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
}

/*void UOpenDoor::OpenDoor() 
{
	OnOpenRequest.Broadcast();
	//Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
	OncloseRequest.Broadcast();
	//Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.f));
}*/

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOfActionsOnPlate() > TriggerMass /*PressurePlate->IsOverlappingActor(Owner)*/) {
		OnOpen.Broadcast();
		//LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	else {
		OnClose.Broadcast();
	}
	
	// check if it's time to close the door.
	/*if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}*/
}

float UOpenDoor::GetTotalMassOfActionsOnPlate() {
	if (!PressurePlate) return 0;
	float TotalMass = 0.f;

	// Find all the overlapping actors
	TArray<AActor*> OverlappingActor;
	PressurePlate->GetOverlappingActors(OUT OverlappingActor);

	for (const auto& Actor : OverlappingActor) {
		//UE_LOG(LogTemp, Warning, TEXT("Actor: %s\n"), *(Actor->GetName()));
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		//actor//->GetComponentByClass<UPrimitive>
	}
	// Iterate through them adding their masses
	UE_LOG(LogTemp, Warning, TEXT("Total mass: %.f\n"), TotalMass);
	return TotalMass;
}