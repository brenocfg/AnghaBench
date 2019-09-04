#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ServerType; int /*<<< orphan*/  FarmControlThread; int /*<<< orphan*/  FarmControlThreadHaltEvent; } ;
typedef  TYPE_1__ SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void SiStopFarmControl(SERVER *s)
{
	// Validate arguments
	if (s == NULL || s->ServerType != SERVER_TYPE_FARM_CONTROLLER)
	{
		return;
	}

	Set(s->FarmControlThreadHaltEvent);
	WaitThread(s->FarmControlThread, INFINITE);
	ReleaseEvent(s->FarmControlThreadHaltEvent);
	ReleaseThread(s->FarmControlThread);
}