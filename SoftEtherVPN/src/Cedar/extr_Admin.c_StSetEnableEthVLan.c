#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {TYPE_1__* Server; } ;
struct TYPE_8__ {int /*<<< orphan*/  IntValue; int /*<<< orphan*/  StrValue; } ;
struct TYPE_7__ {int /*<<< orphan*/ * Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_TEST ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_3__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_NOT_ENOUGH_RIGHT ; 
 int /*<<< orphan*/  ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int GetServerCapsBool (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  MAKEBOOL (int /*<<< orphan*/ ) ; 
 int MsIsAdmin () ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 int SetVLanEnableStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

UINT StSetEnableEthVLan(ADMIN *a, RPC_TEST *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	UINT ret = ERR_NO_ERROR;

	SERVER_ADMIN_ONLY;

#ifdef	OS_WIN32
	if (GetServerCapsBool(s, "b_support_eth_vlan") == false)
	{
		ret = ERR_NOT_SUPPORTED;
	}
	else if (MsIsAdmin() == false)
	{
		ret = ERR_NOT_ENOUGH_RIGHT;
	}
	else
	{
		if (SetVLanEnableStatus(t->StrValue, MAKEBOOL(t->IntValue)) == false)
		{
			ret = ERR_INTERNAL_ERROR;
		}
	}
#else	// OS_WIN32
	ret = ERR_NOT_SUPPORTED;
#endif	// OS_WIN32

	return ret;
}