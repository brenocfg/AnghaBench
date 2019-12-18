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
struct TYPE_4__ {int HaltWatchDog; int /*<<< orphan*/  WatchDogEvent; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/  HubWatchDogThread ; 
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 

void StartHubWatchDog(HUB *h)
{
	THREAD *t;
	// Validate arguments
	if (h == NULL)
	{
		return;
	}

	h->HaltWatchDog = false;
	h->WatchDogEvent = NewEvent();

	t = NewThread(HubWatchDogThread, h);
	WaitThreadInit(t);
	ReleaseThread(t);
}