#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int /*<<< orphan*/  IsWinPcapNeeded; int /*<<< orphan*/  IsBridgeSupportedOs; } ;
typedef  TYPE_1__ RPC_BRIDGE_SUPPORT ;
typedef  int /*<<< orphan*/  EL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  IsBridgeSupported () ; 
 int /*<<< orphan*/  IsNeedWinPcap () ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

UINT EtGetBridgeSupport(EL *a, RPC_BRIDGE_SUPPORT *t)
{
	Zero(t, sizeof(RPC_BRIDGE_SUPPORT));

	t->IsBridgeSupportedOs = IsBridgeSupported();
	t->IsWinPcapNeeded = IsNeedWinPcap();

	return ERR_NO_ERROR;
}