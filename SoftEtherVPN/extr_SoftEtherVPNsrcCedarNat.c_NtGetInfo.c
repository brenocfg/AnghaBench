#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_10__ {TYPE_1__* Cedar; } ;
struct TYPE_9__ {int /*<<< orphan*/  MemInfo; int /*<<< orphan*/  OsInfo; int /*<<< orphan*/  NatHostName; int /*<<< orphan*/  NatBuildInt; int /*<<< orphan*/  NatVerInt; int /*<<< orphan*/  NatBuildInfoString; int /*<<< orphan*/  NatVersionString; int /*<<< orphan*/  NatProductName; } ;
struct TYPE_8__ {int /*<<< orphan*/  Build; int /*<<< orphan*/  BuildInfo; int /*<<< orphan*/  VerString; } ;
typedef  TYPE_2__ RPC_NAT_INFO ;
typedef  int /*<<< orphan*/  OS_INFO ;
typedef  TYPE_3__ NAT ;

/* Variables and functions */
 int /*<<< orphan*/  CEDAR_ROUTER_STR ; 
 int /*<<< orphan*/  CopyOsInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeRpcNatInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  GetMachineName (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetMemInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetOsInfo () ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

UINT NtGetInfo(NAT *n, RPC_NAT_INFO *t)
{
	OS_INFO *info;
	FreeRpcNatInfo(t);
	Zero(t, sizeof(RPC_NAT_INFO));

	StrCpy(t->NatProductName, sizeof(t->NatProductName), CEDAR_ROUTER_STR);
	StrCpy(t->NatVersionString, sizeof(t->NatVersionString), n->Cedar->VerString);
	StrCpy(t->NatBuildInfoString, sizeof(t->NatBuildInfoString), n->Cedar->BuildInfo);
	t->NatVerInt = n->Cedar->Build;
	t->NatBuildInt = n->Cedar->Build;

	GetMachineName(t->NatHostName, sizeof(t->NatHostName));

	info = GetOsInfo();

	CopyOsInfo(&t->OsInfo, info);

	GetMemInfo(&t->MemInfo);

	return ERR_NO_ERROR;
}