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
struct TYPE_7__ {int /*<<< orphan*/  DeviceList; int /*<<< orphan*/  HashedPassword; int /*<<< orphan*/  Port; int /*<<< orphan*/  AutoDeleteCheckDiskFreeSpaceMin; } ;
struct TYPE_6__ {char* DeviceName; int /*<<< orphan*/  NoPromiscuous; int /*<<< orphan*/  LogSetting; } ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_1__ EL_DEVICE ;
typedef  TYPE_2__ EL ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddByte (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CfgAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddInt64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 int ELOG_IS_BETA ; 
 int /*<<< orphan*/  EiWriteLicenseManager (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiWriteHubLogCfgEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void ElSaveConfigToFolder(EL *e, FOLDER *root)
{
	UINT i;
	FOLDER *devices;
	// Validate arguments
	if (e == NULL || root == NULL)
	{
		return;
	}

	CfgAddInt64(root, "AutoDeleteCheckDiskFreeSpaceMin", e->AutoDeleteCheckDiskFreeSpaceMin);

	CfgAddInt(root, "AdminPort", e->Port);

	CfgAddByte(root, "AdminPassword", e->HashedPassword, sizeof(e->HashedPassword));

	if (ELOG_IS_BETA == false)
	{
		EiWriteLicenseManager(CfgCreateFolder(root, "LicenseManager"), e);
	}

	devices = CfgCreateFolder(root,"Devices");

	LockList(e->DeviceList);
	{
		for (i = 0;i < LIST_NUM(e->DeviceList);i++)
		{
			FOLDER *f;
			EL_DEVICE *d = LIST_DATA(e->DeviceList, i);

			f = CfgCreateFolder(devices, d->DeviceName);
			SiWriteHubLogCfgEx(f, &d->LogSetting, true);
			CfgAddBool(f, "NoPromiscuousMode", d->NoPromiscuous);
		}
	}
	UnlockList(e->DeviceList);
}