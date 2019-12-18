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
typedef  int u32 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  MCP_REG_MCPR_GP_INPUTS ; 
 int /*<<< orphan*/  MCP_REG_MCPR_GP_OENABLE ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnx2x_get_epio(struct bnx2x *bp, u32 epio_pin, u32 *en)
{
	u32 epio_mask, gp_oenable;
	*en = 0;
	/* Sanity check */
	if (epio_pin > 31) {
		DP(NETIF_MSG_LINK, "Invalid EPIO pin %d to get\n", epio_pin);
		return;
	}

	epio_mask = 1 << epio_pin;
	/* Set this EPIO to output */
	gp_oenable = REG_RD(bp, MCP_REG_MCPR_GP_OENABLE);
	REG_WR(bp, MCP_REG_MCPR_GP_OENABLE, gp_oenable & ~epio_mask);

	*en = (REG_RD(bp, MCP_REG_MCPR_GP_INPUTS) & epio_mask) >> epio_pin;
}