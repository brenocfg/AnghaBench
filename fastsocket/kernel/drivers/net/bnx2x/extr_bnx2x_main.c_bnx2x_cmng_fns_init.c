#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_5__ {int /*<<< orphan*/  cmng_enables; } ;
struct cmng_init_input {TYPE_2__ flags; scalar_t__ port_rate; } ;
struct TYPE_4__ {scalar_t__ pmf; } ;
struct TYPE_6__ {scalar_t__ line_speed; } ;
struct bnx2x {int /*<<< orphan*/  cmng; TYPE_1__ port; TYPE_3__ link_vars; } ;

/* Variables and functions */
 int BP_MAX_VN_NUM (struct bnx2x*) ; 
 int /*<<< orphan*/  CMNG_FLAGS_PER_PORT_RATE_SHAPING_VN ; 
 scalar_t__ CMNG_FNS_MINMAX ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NETIF_MSG_IFUP ; 
 int VN_0 ; 
 int /*<<< orphan*/  bnx2x_calc_vn_max (struct bnx2x*,int,struct cmng_init_input*) ; 
 int /*<<< orphan*/  bnx2x_calc_vn_min (struct bnx2x*,struct cmng_init_input*) ; 
 int /*<<< orphan*/  bnx2x_init_cmng (struct cmng_init_input*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2x_read_mf_cfg (struct bnx2x*) ; 
 int /*<<< orphan*/  memset (struct cmng_init_input*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnx2x_cmng_fns_init(struct bnx2x *bp, u8 read_cfg, u8 cmng_type)
{
	struct cmng_init_input input;
	memset(&input, 0, sizeof(struct cmng_init_input));

	input.port_rate = bp->link_vars.line_speed;

	if (cmng_type == CMNG_FNS_MINMAX && input.port_rate) {
		int vn;

		/* read mf conf from shmem */
		if (read_cfg)
			bnx2x_read_mf_cfg(bp);

		/* vn_weight_sum and enable fairness if not 0 */
		bnx2x_calc_vn_min(bp, &input);

		/* calculate and set min-max rate for each vn */
		if (bp->port.pmf)
			for (vn = VN_0; vn < BP_MAX_VN_NUM(bp); vn++)
				bnx2x_calc_vn_max(bp, vn, &input);

		/* always enable rate shaping and fairness */
		input.flags.cmng_enables |=
					CMNG_FLAGS_PER_PORT_RATE_SHAPING_VN;

		bnx2x_init_cmng(&input, &bp->cmng);
		return;
	}

	/* rate shaping and fairness are disabled */
	DP(NETIF_MSG_IFUP,
	   "rate shaping and fairness are disabled\n");
}