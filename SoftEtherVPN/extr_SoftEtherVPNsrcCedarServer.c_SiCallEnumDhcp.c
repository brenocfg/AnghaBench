#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SERVER ;
typedef  int /*<<< orphan*/  RPC_ENUM_DHCP ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  FARM_MEMBER ;

/* Variables and functions */
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcEnumDhcp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * SiCallTask (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

void SiCallEnumDhcp(SERVER *s, FARM_MEMBER *f, char *hubname, RPC_ENUM_DHCP *t)
{
	PACK *p;
	// Validate arguments
	if (s == NULL || f == NULL || hubname == NULL || t == NULL)
	{
		return;
	}

	p = NewPack();
	PackAddStr(p, "HubName", hubname);

	p = SiCallTask(f, p, "enumdhcp");

	Zero(t, sizeof(RPC_ENUM_DHCP));
	InRpcEnumDhcp(t, p);

	FreePack(p);
}