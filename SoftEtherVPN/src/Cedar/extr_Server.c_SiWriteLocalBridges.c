#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
typedef  scalar_t__ UINT ;
struct TYPE_5__ {TYPE_1__* Cedar; } ;
struct TYPE_4__ {int /*<<< orphan*/  LocalBridgeList; } ;
typedef  TYPE_2__ SERVER ;
typedef  int /*<<< orphan*/  LOCALBRIDGE ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Format (char*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  GSF_LOCALBRIDGE_NO_DISABLE_OFFLOAD ; 
 int /*<<< orphan*/  GetGlobalServerFlag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  SiWriteLocalBridgeCfg (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Win32EthGetShowAllIf () ; 
 int /*<<< orphan*/  Win32GetEnableSeLow () ; 

void SiWriteLocalBridges(FOLDER *f, SERVER *s)
{
	// Validate arguments
	if (s == NULL || f == NULL)
	{
		return;
	}

#ifdef	OS_WIN32
	CfgAddBool(f, "ShowAllInterfaces", Win32EthGetShowAllIf());

	CfgAddBool(f, "EnableSoftEtherKernelModeDriver", Win32GetEnableSeLow());
#endif	// OS_WIN32

#ifdef	UNIX_LINUX
	CfgAddBool(f, "DoNotDisableOffloading", GetGlobalServerFlag(GSF_LOCALBRIDGE_NO_DISABLE_OFFLOAD));
#endif	// UNIX_LINUX

	LockList(s->Cedar->LocalBridgeList);
	{
		UINT i;
		for (i = 0;i < LIST_NUM(s->Cedar->LocalBridgeList);i++)
		{
			LOCALBRIDGE *br = LIST_DATA(s->Cedar->LocalBridgeList, i);
			char name[MAX_SIZE];

			Format(name, sizeof(name), "LocalBridge%u", i);
			SiWriteLocalBridgeCfg(CfgCreateFolder(f, name), br);
		}
	}
	UnlockList(s->Cedar->LocalBridgeList);
}