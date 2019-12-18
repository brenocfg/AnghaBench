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
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  hubname ;
typedef  int /*<<< orphan*/  SERVER ;
typedef  int /*<<< orphan*/  RPC_ENUM_MAC_TABLE ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  FreeRpcEnumMacTable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  OutRpcEnumMacTable (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PackGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  SiEnumMacTable (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

PACK *SiCalledEnumMacTable(SERVER *s, PACK *p)
{
	char hubname[MAX_HUBNAME_LEN + 1];
	RPC_ENUM_MAC_TABLE t;
	PACK *ret;
	// Validate arguments
	if (s == NULL || p == NULL)
	{
		return NewPack();
	}
	if (PackGetStr(p, "HubName", hubname, sizeof(hubname)) == false)
	{
		return NewPack();
	}
	Zero(&t, sizeof(t));

	SiEnumMacTable(s, hubname, &t);

	ret = NewPack();
	OutRpcEnumMacTable(ret, &t);
	FreeRpcEnumMacTable(&t);

	return ret;
}