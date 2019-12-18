#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
struct TYPE_10__ {int /*<<< orphan*/  DeviceList; } ;
struct TYPE_9__ {int Halt; int /*<<< orphan*/  Thread; int /*<<< orphan*/  Cancel1; int /*<<< orphan*/  DeviceName; } ;
typedef  TYPE_1__ EL_DEVICE ;
typedef  TYPE_2__ EL ;

/* Variables and functions */
 int /*<<< orphan*/  Cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 
 TYPE_1__* Search (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

bool ElDeleteCaptureDevice(EL *e, char *name)
{
	bool ret = false;
	EL_DEVICE *d, t;
	// Validate arguments
	if (e == NULL || name == NULL)
	{
		return false;
	}

	LockList(e->DeviceList);
	{
		Zero(&t, sizeof(t));
		StrCpy(t.DeviceName, sizeof(t.DeviceName), name);

		d = Search(e->DeviceList, &t);

		if (d != NULL)
		{
			// Stop capture
			d->Halt = true;
			Cancel(d->Cancel1);

			// Wait for thread stop
			WaitThread(d->Thread, INFINITE);
			ReleaseThread(d->Thread);

			// Release the memory
			Delete(e->DeviceList, d);
			Free(d);

			ret = true;
		}
	}
	UnlockList(e->DeviceList);

	return ret;
}