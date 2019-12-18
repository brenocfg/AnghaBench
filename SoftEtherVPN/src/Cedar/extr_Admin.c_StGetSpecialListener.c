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
struct TYPE_8__ {int /*<<< orphan*/  VpnOverIcmpListener; int /*<<< orphan*/  VpnOverDnsListener; } ;
struct TYPE_7__ {int /*<<< orphan*/  EnableVpnOverIcmp; int /*<<< orphan*/  EnableVpnOverDns; int /*<<< orphan*/ * Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_SPECIAL_LISTENER ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_3__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  NO_SUPPORT_FOR_BRIDGE ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

UINT StGetSpecialListener(ADMIN *a, RPC_SPECIAL_LISTENER *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	UINT ret = ERR_NO_ERROR;

	SERVER_ADMIN_ONLY;
	NO_SUPPORT_FOR_BRIDGE;

	Zero(t, sizeof(RPC_SPECIAL_LISTENER));
	t->VpnOverDnsListener = s->EnableVpnOverDns;
	t->VpnOverIcmpListener = s->EnableVpnOverIcmp;

	return ERR_NO_ERROR;
}