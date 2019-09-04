#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
struct TYPE_12__ {int /*<<< orphan*/  DeviceList; } ;
struct TYPE_11__ {int NoPromiscuous; int /*<<< orphan*/  Thread; TYPE_2__* el; int /*<<< orphan*/  LogSetting; int /*<<< orphan*/  DeviceName; } ;
typedef  int /*<<< orphan*/  HUB_LOG ;
typedef  TYPE_1__ EL_DEVICE ;
typedef  TYPE_2__ EL ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ElCaptureThread ; 
 int /*<<< orphan*/  ElSaveConfig (TYPE_2__*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* Search (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

bool ElAddCaptureDevice(EL *e, char *name, HUB_LOG *log, bool no_promiscuous)
{
	EL_DEVICE *d, t;
	// Validate arguments
	if (e == NULL || name == NULL || log == NULL)
	{
		return false;
	}

	Zero(&t, sizeof(t));
	StrCpy(t.DeviceName, sizeof(t.DeviceName), name);

	LockList(e->DeviceList);
	{
		d = Search(e->DeviceList, &t);
		if (d != NULL)
		{
			// Capture settings with the same name already exists
			UnlockList(e->DeviceList);
			return false;
		}

		// Add a device
		d = ZeroMalloc(sizeof(EL_DEVICE));
		StrCpy(d->DeviceName, sizeof(d->DeviceName), name);
		Copy(&d->LogSetting, log, sizeof(HUB_LOG));
		d->NoPromiscuous = no_promiscuous;
		d->el = e;
		Insert(e->DeviceList, d);

		// Start the thread
		d->Thread = NewThread(ElCaptureThread, d);
		WaitThreadInit(d->Thread);
	}
	UnlockList(e->DeviceList);

	ElSaveConfig(e);

	return true;
}