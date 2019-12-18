#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_5__ {int /*<<< orphan*/ * PacketLogConfig; void* PacketLogSwitchType; void* SavePacketLog; void* SecurityLogSwitchType; void* SaveSecurityLog; } ;
struct TYPE_6__ {TYPE_1__ LogSetting; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_2__ RPC_HUB_LOG ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 size_t NUM_PACKET_LOG ; 
 void* PackGetBool (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetIntEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

void InRpcHubLog(RPC_HUB_LOG *t, PACK *p)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_HUB_LOG));
	PackGetStr(p, "HubName", t->HubName, sizeof(t->HubName));
	t->LogSetting.SaveSecurityLog = PackGetBool(p, "SaveSecurityLog");
	t->LogSetting.SecurityLogSwitchType = PackGetInt(p, "SecurityLogSwitchType");
	t->LogSetting.SavePacketLog = PackGetBool(p, "SavePacketLog");
	t->LogSetting.PacketLogSwitchType = PackGetInt(p, "PacketLogSwitchType");
	for (i = 0;i < NUM_PACKET_LOG;i++)
	{
		t->LogSetting.PacketLogConfig[i] = PackGetIntEx(p, "PacketLogConfig", i);
	}
}