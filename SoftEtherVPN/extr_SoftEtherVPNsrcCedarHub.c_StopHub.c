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
struct TYPE_4__ {int Offline; int HubIsOnlineButHalting; int Halt; int /*<<< orphan*/  Name; int /*<<< orphan*/  Cedar; } ;
typedef  TYPE_1__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/  SLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetHubOffline (TYPE_1__*) ; 

void StopHub(HUB *h)
{
	bool old_status = false;
	// Validate arguments
	if (h == NULL)
	{
		return;
	}

	old_status = h->Offline;
	h->HubIsOnlineButHalting = true;

	SetHubOffline(h);

	if (h->Halt == false)
	{
		SLog(h->Cedar, "LS_HUB_STOP", h->Name);
		h->Halt = true;
	}

	h->Offline = old_status;
	h->HubIsOnlineButHalting = false;
}