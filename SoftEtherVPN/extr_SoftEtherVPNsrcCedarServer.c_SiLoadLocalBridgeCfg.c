#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  tapaddr ;
typedef  int /*<<< orphan*/  nic ;
typedef  int /*<<< orphan*/  hub ;
typedef  char UCHAR ;
struct TYPE_9__ {int /*<<< orphan*/  OsType; } ;
struct TYPE_8__ {int Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_7__ {int /*<<< orphan*/  Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  AddLocalBridge (int /*<<< orphan*/ ,char*,char*,scalar_t__,scalar_t__,int,char*,scalar_t__) ; 
 scalar_t__ CfgGetBool (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ CfgGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  Copy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 TYPE_5__* GetOsInfo () ; 
 scalar_t__ IsEmptyStr (char*) ; 
 int MAX_SIZE ; 
 scalar_t__ OS_IS_UNIX (int /*<<< orphan*/ ) ; 
 TYPE_2__* StrToBin (char*) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 

void SiLoadLocalBridgeCfg(SERVER *s, FOLDER *f)
{
	char hub[MAX_SIZE];
	char nic[MAX_SIZE];
	bool tapmode = false;
	UCHAR tapaddr[6];
	// Validate arguments
	if (s == NULL || f == NULL)
	{
		return;
	}

	Zero(hub, sizeof(hub));
	Zero(nic, sizeof(nic));

	CfgGetStr(f, "HubName", hub, sizeof(hub));
	CfgGetStr(f, "DeviceName", nic, sizeof(nic));

	if (IsEmptyStr(hub) || IsEmptyStr(nic)
		)
	{
		return;
	}

	if (OS_IS_UNIX(GetOsInfo()->OsType))
	{
		if (CfgGetBool(f, "TapMode"))
		{
			char tmp[MAX_SIZE];
			tapmode = true;
			Zero(tapaddr, sizeof(tapaddr));
			if (CfgGetStr(f, "TapMacAddress", tmp, sizeof(tmp)))
			{
				BUF *b;
				b = StrToBin(tmp);
				if (b != NULL && b->Size == 6)
				{
					Copy(tapaddr, b->Buf, sizeof(tapaddr));
				}
				FreeBuf(b);
			}
		}
	}

	AddLocalBridge(s->Cedar, hub, nic, CfgGetBool(f, "NoPromiscuousMode"), CfgGetBool(f, "MonitorMode"),
		tapmode, tapaddr, CfgGetBool(f, "LimitBroadcast"));
}