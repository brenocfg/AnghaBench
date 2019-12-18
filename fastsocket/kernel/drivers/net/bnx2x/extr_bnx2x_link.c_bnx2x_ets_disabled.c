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
struct link_vars {int dummy; } ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E2 (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E3A0 (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E3B0 (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  bnx2x_ets_e2e3a0_disabled (struct link_params*) ; 
 int bnx2x_ets_e3b0_disabled (struct link_params*,struct link_vars*) ; 

int bnx2x_ets_disabled(struct link_params *params,
		      struct link_vars *vars)
{
	struct bnx2x *bp = params->bp;
	int bnx2x_status = 0;

	if ((CHIP_IS_E2(bp)) || (CHIP_IS_E3A0(bp)))
		bnx2x_ets_e2e3a0_disabled(params);
	else if (CHIP_IS_E3B0(bp))
		bnx2x_status = bnx2x_ets_e3b0_disabled(params, vars);
	else {
		DP(NETIF_MSG_LINK, "bnx2x_ets_disabled - chip not supported\n");
		return -EINVAL;
	}

	return bnx2x_status;
}