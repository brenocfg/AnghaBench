#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  g ;
typedef  int UINT ;
struct TYPE_9__ {int Port; scalar_t__ AutoDeleteCheckDiskFreeSpaceMin; int /*<<< orphan*/  DeviceList; int /*<<< orphan*/  HashedPassword; } ;
struct TYPE_8__ {int NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  HUB_LOG ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_2__ EL ;

/* Variables and functions */
 TYPE_1__* CfgEnumFolderToTokenList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CfgGetBool (int /*<<< orphan*/ *,char*) ; 
 int CfgGetByte (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * CfgGetFolder (int /*<<< orphan*/ *,char*) ; 
 int CfgGetInt (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ CfgGetInt64 (int /*<<< orphan*/ *,char*) ; 
 int CfgIsItem (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ DISK_FREE_SPACE_DEFAULT ; 
 scalar_t__ DISK_FREE_SPACE_MIN ; 
 int ELOG_IS_BETA ; 
 int /*<<< orphan*/  EiLoadLicenseManager (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ElAddCaptureDevice (TYPE_2__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiLoadHubLogCfg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

void ElLoadConfigFromFolder(EL *e, FOLDER *root)
{
	UINT i;
	TOKEN_LIST *t;
	FOLDER *devices;

	// Validate arguments
	if (e == NULL || root == NULL)
	{
		return;
	}

	i = CfgGetInt(root, "AdminPort");
	if (i >= 1 && i <= 65535)
	{
		e->Port = i;
	}

	e->AutoDeleteCheckDiskFreeSpaceMin = CfgGetInt64(root, "AutoDeleteCheckDiskFreeSpaceMin");
	if (CfgIsItem(root, "AutoDeleteCheckDiskFreeSpaceMin") == false && e->AutoDeleteCheckDiskFreeSpaceMin == 0)
	{
		e->AutoDeleteCheckDiskFreeSpaceMin = DISK_FREE_SPACE_DEFAULT;
	}

	if (e->AutoDeleteCheckDiskFreeSpaceMin != 0)
	{
		if (e->AutoDeleteCheckDiskFreeSpaceMin < DISK_FREE_SPACE_MIN)
		{
			e->AutoDeleteCheckDiskFreeSpaceMin = DISK_FREE_SPACE_MIN;
		}
	}

	if (CfgGetByte(root, "AdminPassword", e->HashedPassword, sizeof(e->HashedPassword)) != sizeof(e->HashedPassword))
	{
		Sha0(e->HashedPassword, "", 0);
	}

	if (ELOG_IS_BETA == false)
	{
		EiLoadLicenseManager(e,	CfgGetFolder(root, "LicenseManager"));
	}

	devices = CfgGetFolder(root, "Devices");
	if(devices != NULL)
	{
		LockList(e->DeviceList);
		{
			t = CfgEnumFolderToTokenList(devices);
			for (i = 0;i < t->NumTokens;i++)
			{
				char *name = t->Token[i];
				FOLDER *f = CfgGetFolder(devices, name);

				if (f != NULL)
				{
					HUB_LOG g;

					Zero(&g, sizeof(g));
					SiLoadHubLogCfg(&g, f);
					ElAddCaptureDevice(e, name, &g, CfgGetBool(f, "NoPromiscuousMode"));
				}
			}
			FreeToken(t);
		}
		UnlockList(e->DeviceList);
	}
}