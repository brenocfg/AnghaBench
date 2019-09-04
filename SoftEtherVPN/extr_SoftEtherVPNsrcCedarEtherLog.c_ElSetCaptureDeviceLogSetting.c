#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
struct TYPE_12__ {int /*<<< orphan*/  DeviceList; } ;
struct TYPE_11__ {int /*<<< orphan*/  Logger; int /*<<< orphan*/  LogSetting; int /*<<< orphan*/  DeviceName; } ;
struct TYPE_10__ {int /*<<< orphan*/  PacketLogSwitchType; } ;
typedef  TYPE_1__ HUB_LOG ;
typedef  TYPE_2__ EL_DEVICE ;
typedef  TYPE_3__ EL ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 TYPE_2__* Search (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  SetLogSwitchType (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

bool ElSetCaptureDeviceLogSetting(EL *e, char *name, HUB_LOG *log)
{
	EL_DEVICE *d;
	bool ret = false;
	// Validate arguments
	if (e == NULL || log == NULL || name == NULL)
	{
		return false;
	}

	LockList(e->DeviceList);
	{
		EL_DEVICE t;

		Zero(&t, sizeof(t));
		StrCpy(t.DeviceName, sizeof(t.DeviceName), name);

		d = Search(e->DeviceList, &t);

		if (d != NULL)
		{
			Copy(&d->LogSetting, log, sizeof(HUB_LOG));

			SetLogSwitchType(d->Logger, log->PacketLogSwitchType);

			ret = true;
		}
	}
	UnlockList(e->DeviceList);

	return ret;
}