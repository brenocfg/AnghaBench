#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_5__ {int /*<<< orphan*/  OsType; } ;
struct TYPE_4__ {char* DeviceName; char* HubName; int /*<<< orphan*/  TapMacAddress; scalar_t__ TapMode; scalar_t__ LimitBroadcast; scalar_t__ Monitor; scalar_t__ Local; } ;
typedef  TYPE_1__ LOCALBRIDGE ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  CfgAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 TYPE_3__* GetOsInfo () ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MacToStr (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ OS_IS_UNIX (int /*<<< orphan*/ ) ; 

void SiWriteLocalBridgeCfg(FOLDER *f, LOCALBRIDGE *br)
{
	// Validate arguments
	if (f == NULL || br == NULL)
	{
		return;
	}

	CfgAddStr(f, "DeviceName", br->DeviceName);
	CfgAddStr(f, "HubName", br->HubName);
	CfgAddBool(f, "NoPromiscuousMode", br->Local);
	CfgAddBool(f, "MonitorMode", br->Monitor);
	CfgAddBool(f, "LimitBroadcast", br->LimitBroadcast);

	if (OS_IS_UNIX(GetOsInfo()->OsType))
	{
		CfgAddBool(f, "TapMode", br->TapMode);

		if (br->TapMode)
		{
			char tmp[MAX_SIZE];
			MacToStr(tmp, sizeof(tmp), br->TapMacAddress);
			CfgAddStr(f, "TapMacAddress", tmp);
		}
	}
}