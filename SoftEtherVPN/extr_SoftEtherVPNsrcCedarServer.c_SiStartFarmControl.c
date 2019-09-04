#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ServerType; int /*<<< orphan*/  FarmControlThread; int /*<<< orphan*/  FarmControlThreadHaltEvent; } ;
typedef  TYPE_1__ SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 int /*<<< orphan*/  SiFarmControlThread ; 

void SiStartFarmControl(SERVER *s)
{
	// Validate arguments
	if (s == NULL || s->ServerType != SERVER_TYPE_FARM_CONTROLLER)
	{
		return;
	}

	s->FarmControlThreadHaltEvent = NewEvent();
	s->FarmControlThread = NewThread(SiFarmControlThread, s);
}