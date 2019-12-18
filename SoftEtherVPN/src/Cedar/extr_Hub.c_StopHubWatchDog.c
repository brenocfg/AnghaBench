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
struct TYPE_3__ {int HaltWatchDog; int /*<<< orphan*/ * WatchDogEvent; int /*<<< orphan*/ * WatchDogThread; } ;
typedef  TYPE_1__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void StopHubWatchDog(HUB *h)
{
	// Validate arguments
	if (h == NULL)
	{
		return;
	}

	h->HaltWatchDog = true;
	Set(h->WatchDogEvent);

	WaitThread(h->WatchDogThread, INFINITE);
	ReleaseThread(h->WatchDogThread);
	h->WatchDogThread = NULL;
	h->HaltWatchDog = false;

	ReleaseEvent(h->WatchDogEvent);
	h->WatchDogEvent = NULL;
}