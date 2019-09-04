#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  Guid; int /*<<< orphan*/  FileName; int /*<<< orphan*/  Version; int /*<<< orphan*/  MacAddress; int /*<<< orphan*/  Enabled; int /*<<< orphan*/  DeviceName; } ;
typedef  TYPE_1__ RPC_CLIENT_GET_VLAN ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcClientGetVLan(PACK *p, RPC_CLIENT_GET_VLAN *v)
{
	// Validate arguments
	if (v == NULL || p == NULL)
	{
		return;
	}

	PackAddStr(p, "DeviceName", v->DeviceName);
	PackAddInt(p, "Enabled", v->Enabled);
	PackAddStr(p, "MacAddress", v->MacAddress);
	PackAddStr(p, "Version", v->Version);
	PackAddStr(p, "FileName", v->FileName);
	PackAddStr(p, "Guid", v->Guid);
}