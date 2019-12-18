#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {TYPE_3__* app_pri_tbl; int /*<<< orphan*/  enabled; int /*<<< orphan*/  tc_supported; int /*<<< orphan*/  default_pri; } ;
struct TYPE_6__ {int /*<<< orphan*/  enabled; int /*<<< orphan*/  pfc_caps; int /*<<< orphan*/  pri_en_bitmap; } ;
struct TYPE_5__ {int /*<<< orphan*/  pri_pg_tbl; int /*<<< orphan*/  pg_bw_tbl; int /*<<< orphan*/  enabled; } ;
struct dcbx_features {TYPE_4__ app; TYPE_2__ pfc; TYPE_1__ ets; } ;
struct bnx2x {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  appBitfield; int /*<<< orphan*/  pri_bitmap; int /*<<< orphan*/  app_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_DCB ; 
 size_t DCBX_MAX_APP_PROTOCOL ; 
 size_t DCBX_MAX_NUM_PG_BW_ENTRIES ; 
 size_t DCBX_MAX_NUM_PRI_PG_ENTRIES ; 
 int /*<<< orphan*/  DCBX_PG_BW_GET (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  DCBX_PRI_PG_GET (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 

__attribute__((used)) static void  bnx2x_dump_dcbx_drv_param(struct bnx2x *bp,
				       struct dcbx_features *features,
				       u32 error)
{
	u8 i = 0;
	DP(NETIF_MSG_LINK, "local_mib.error %x\n", error);

	/* PG */
	DP(NETIF_MSG_LINK,
	   "local_mib.features.ets.enabled %x\n", features->ets.enabled);
	for (i = 0; i < DCBX_MAX_NUM_PG_BW_ENTRIES; i++)
		DP(NETIF_MSG_LINK,
		   "local_mib.features.ets.pg_bw_tbl[%d] %d\n", i,
		   DCBX_PG_BW_GET(features->ets.pg_bw_tbl, i));
	for (i = 0; i < DCBX_MAX_NUM_PRI_PG_ENTRIES; i++)
		DP(NETIF_MSG_LINK,
		   "local_mib.features.ets.pri_pg_tbl[%d] %d\n", i,
		   DCBX_PRI_PG_GET(features->ets.pri_pg_tbl, i));

	/* pfc */
	DP(BNX2X_MSG_DCB, "dcbx_features.pfc.pri_en_bitmap %x\n",
					features->pfc.pri_en_bitmap);
	DP(BNX2X_MSG_DCB, "dcbx_features.pfc.pfc_caps %x\n",
					features->pfc.pfc_caps);
	DP(BNX2X_MSG_DCB, "dcbx_features.pfc.enabled %x\n",
					features->pfc.enabled);

	DP(BNX2X_MSG_DCB, "dcbx_features.app.default_pri %x\n",
					features->app.default_pri);
	DP(BNX2X_MSG_DCB, "dcbx_features.app.tc_supported %x\n",
					features->app.tc_supported);
	DP(BNX2X_MSG_DCB, "dcbx_features.app.enabled %x\n",
					features->app.enabled);
	for (i = 0; i < DCBX_MAX_APP_PROTOCOL; i++) {
		DP(BNX2X_MSG_DCB,
		   "dcbx_features.app.app_pri_tbl[%x].app_id %x\n",
		   i, features->app.app_pri_tbl[i].app_id);
		DP(BNX2X_MSG_DCB,
		   "dcbx_features.app.app_pri_tbl[%x].pri_bitmap %x\n",
		   i, features->app.app_pri_tbl[i].pri_bitmap);
		DP(BNX2X_MSG_DCB,
		   "dcbx_features.app.app_pri_tbl[%x].appBitfield %x\n",
		   i, features->app.app_pri_tbl[i].appBitfield);
	}
}