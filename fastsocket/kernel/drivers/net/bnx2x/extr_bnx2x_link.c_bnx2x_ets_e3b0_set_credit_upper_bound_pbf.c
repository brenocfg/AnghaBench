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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct link_params {int port; struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int DCBX_E3B0_MAX_NUM_COS_PORT0 ; 
 int DCBX_E3B0_MAX_NUM_COS_PORT1 ; 
 scalar_t__ PBF_REG_COS0_UPPER_BOUND_P0 ; 
 scalar_t__ PBF_REG_COS0_UPPER_BOUND_P1 ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,scalar_t__ const) ; 
 scalar_t__ bnx2x_ets_get_credit_upper_bound (scalar_t__ const) ; 

__attribute__((used)) static void bnx2x_ets_e3b0_set_credit_upper_bound_pbf(
	const struct link_params *params,
	const u32 min_w_val)
{
	struct bnx2x *bp = params->bp;
	const u32 credit_upper_bound =
	    bnx2x_ets_get_credit_upper_bound(min_w_val);
	const u8 port = params->port;
	u32 base_upper_bound = 0;
	u8 max_cos = 0;
	u8 i = 0;
	/* In 2 port mode port0 has COS0-5 that can be used for WFQ.In 4
	 * port mode port1 has COS0-2 that can be used for WFQ.
	 */
	if (!port) {
		base_upper_bound = PBF_REG_COS0_UPPER_BOUND_P0;
		max_cos = DCBX_E3B0_MAX_NUM_COS_PORT0;
	} else {
		base_upper_bound = PBF_REG_COS0_UPPER_BOUND_P1;
		max_cos = DCBX_E3B0_MAX_NUM_COS_PORT1;
	}

	for (i = 0; i < max_cos; i++)
		REG_WR(bp, base_upper_bound + (i << 2), credit_upper_bound);
}