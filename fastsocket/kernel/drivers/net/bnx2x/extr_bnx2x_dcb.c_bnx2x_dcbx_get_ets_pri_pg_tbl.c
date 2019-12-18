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
typedef  int /*<<< orphan*/  u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_DCB ; 
 int DCBX_MAX_NUM_PRI_PG_ENTRIES ; 
 int /*<<< orphan*/  DCBX_PRI_PG_GET (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_dcbx_get_ets_pri_pg_tbl(struct bnx2x *bp,
				u32 *set_configuration_ets_pg,
				u32 *pri_pg_tbl)
{
	int i;

	for (i = 0; i < DCBX_MAX_NUM_PRI_PG_ENTRIES; i++) {
		set_configuration_ets_pg[i] = DCBX_PRI_PG_GET(pri_pg_tbl, i);

		DP(BNX2X_MSG_DCB, "set_configuration_ets_pg[%d] = 0x%x\n",
		   i, set_configuration_ets_pg[i]);
	}
}