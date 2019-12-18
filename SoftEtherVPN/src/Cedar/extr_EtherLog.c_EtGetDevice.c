#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  a ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_11__ {int /*<<< orphan*/  DeviceList; } ;
struct TYPE_10__ {int /*<<< orphan*/  NoPromiscuous; int /*<<< orphan*/  LogSetting; int /*<<< orphan*/  DeviceName; } ;
struct TYPE_9__ {int /*<<< orphan*/  NoPromiscuous; int /*<<< orphan*/  LogSetting; int /*<<< orphan*/  DeviceName; } ;
typedef  TYPE_1__ RPC_ADD_DEVICE ;
typedef  int /*<<< orphan*/  HUB_LOG ;
typedef  TYPE_2__ EL_DEVICE ;
typedef  TYPE_3__ EL ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ERR_CAPTURE_NOT_FOUND ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 TYPE_2__* Search (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

UINT EtGetDevice(EL *e, RPC_ADD_DEVICE *t)
{
	UINT ret = ERR_CAPTURE_NOT_FOUND;

	LockList(e->DeviceList);
	{
		EL_DEVICE *d, a;
		Zero(&a, sizeof(a));
		StrCpy(a.DeviceName, sizeof(a.DeviceName), t->DeviceName);

		d = Search(e->DeviceList, &a);

		if (d != NULL)
		{
			ret = ERR_NO_ERROR;

			Copy(&t->LogSetting, &d->LogSetting, sizeof(HUB_LOG));
			t->NoPromiscuous = d->NoPromiscuous;
		}
	}
	UnlockList(e->DeviceList);

	return ret;
}