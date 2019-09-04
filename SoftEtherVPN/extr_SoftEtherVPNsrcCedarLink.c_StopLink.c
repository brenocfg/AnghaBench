#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int Started; int Halting; int /*<<< orphan*/ * ClientSession; TYPE_1__* Cedar; } ;
struct TYPE_6__ {int /*<<< orphan*/  CurrentActiveLinks; } ;
typedef  TYPE_2__ LINK ;

/* Variables and functions */
 int /*<<< orphan*/  Dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockLink (TYPE_2__*) ; 
 int /*<<< orphan*/  ReleaseSession (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StopSession (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockLink (TYPE_2__*) ; 

void StopLink(LINK *k)
{
	// Validate arguments
	if (k == NULL)
	{
		return;
	}

	LockLink(k);
	{
		if (k->Started == false)
		{
			UnlockLink(k);
			return;
		}
		k->Started = false;
		k->Halting = true;

		Dec(k->Cedar->CurrentActiveLinks);
	}
	UnlockLink(k);

	if (k->ClientSession != NULL)
	{
		// Disconnect the client session
		StopSession(k->ClientSession);

		LockLink(k);
		{
			ReleaseSession(k->ClientSession);
			k->ClientSession = NULL;
		}
		UnlockLink(k);
	}

	LockLink(k);
	{
		k->Halting = false;
	}
	UnlockLink(k);
}