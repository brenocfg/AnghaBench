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
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int /*<<< orphan*/ * DeviceList; int /*<<< orphan*/  CfgRw; } ;
struct TYPE_6__ {int /*<<< orphan*/  DeviceName; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ EL_DEVICE ;
typedef  TYPE_2__ EL ;

/* Variables and functions */
 int /*<<< orphan*/  CopyStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ElDeleteCaptureDevice (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  ElSaveConfig (TYPE_2__*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeCfgRw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 

void ElFreeConfig(EL *e)
{
	UINT i;
	LIST *o;
	// Validate arguments
	if (e == NULL)
	{
		return;
	}

	// Write the configuration file
	ElSaveConfig(e);
	FreeCfgRw(e->CfgRw);

	// Stop all capture
	o = NewList(NULL);
	LockList(e->DeviceList);
	{
		for (i = 0;i < LIST_NUM(e->DeviceList);i++)
		{
			EL_DEVICE *d = LIST_DATA(e->DeviceList, i);
			Insert(o, CopyStr(d->DeviceName));
		}
		for (i = 0;i < LIST_NUM(o);i++)
		{
			char *name = LIST_DATA(o, i);
			ElDeleteCaptureDevice(e, name);
			Free(name);
		}
		ReleaseList(o);
	}
	UnlockList(e->DeviceList);

	ReleaseList(e->DeviceList);
}