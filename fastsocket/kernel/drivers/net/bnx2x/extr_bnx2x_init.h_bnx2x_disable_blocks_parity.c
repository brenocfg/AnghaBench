#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct bnx2x {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  mask_addr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  NETIF_MSG_HW ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* bnx2x_blocks_parity_data ; 
 scalar_t__ bnx2x_parity_reg_mask (struct bnx2x*,int) ; 
 int /*<<< orphan*/  bnx2x_set_mcp_parity (struct bnx2x*,int) ; 

__attribute__((used)) static inline void bnx2x_disable_blocks_parity(struct bnx2x *bp)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(bnx2x_blocks_parity_data); i++) {
		u32 dis_mask = bnx2x_parity_reg_mask(bp, i);

		if (dis_mask) {
			REG_WR(bp, bnx2x_blocks_parity_data[i].mask_addr,
			       dis_mask);
			DP(NETIF_MSG_HW, "Setting parity mask "
						 "for %s to\t\t0x%x\n",
				    bnx2x_blocks_parity_data[i].name, dis_mask);
		}
	}

	/* Disable MCP parity attentions */
	bnx2x_set_mcp_parity(bp, false);
}