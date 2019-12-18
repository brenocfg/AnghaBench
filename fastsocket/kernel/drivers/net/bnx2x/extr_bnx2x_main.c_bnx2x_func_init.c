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
struct tstorm_eth_function_common_config {int /*<<< orphan*/  member_0; } ;
struct bnx2x_func_init_params {int func_flgs; int /*<<< orphan*/  spq_prod; int /*<<< orphan*/  func_id; int /*<<< orphan*/  spq_map; int /*<<< orphan*/  pf_id; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1x (struct bnx2x*) ; 
 int FUNC_FLG_SPQ ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ XSEM_REG_FAST_MEMORY ; 
 scalar_t__ XSTORM_SPQ_PROD_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storm_memset_func_cfg (struct bnx2x*,struct tstorm_eth_function_common_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storm_memset_func_en (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  storm_memset_spq_addr (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storm_memset_vf_to_pf (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bnx2x_func_init(struct bnx2x *bp, struct bnx2x_func_init_params *p)
{
	if (CHIP_IS_E1x(bp)) {
		struct tstorm_eth_function_common_config tcfg = {0};

		storm_memset_func_cfg(bp, &tcfg, p->func_id);
	}

	/* Enable the function in the FW */
	storm_memset_vf_to_pf(bp, p->func_id, p->pf_id);
	storm_memset_func_en(bp, p->func_id, 1);

	/* spq */
	if (p->func_flgs & FUNC_FLG_SPQ) {
		storm_memset_spq_addr(bp, p->spq_map, p->func_id);
		REG_WR(bp, XSEM_REG_FAST_MEMORY +
		       XSTORM_SPQ_PROD_OFFSET(p->func_id), p->spq_prod);
	}
}