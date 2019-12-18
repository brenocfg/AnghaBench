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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct link_params {int port; struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int GRCBASE_UMAC0 ; 
 int GRCBASE_UMAC1 ; 
 int MISC_REGISTERS_RESET_REG_2_UMAC0 ; 
 int MISC_REG_RESET_REG_2 ; 
 int REG_RD (struct bnx2x*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int,int) ; 
 int UMAC_COMMAND_CONFIG_REG_RX_ENA ; 
 int UMAC_COMMAND_CONFIG_REG_TX_ENA ; 
 int UMAC_REG_COMMAND_CONFIG ; 

__attribute__((used)) static void bnx2x_set_umac_rxtx(struct link_params *params, u8 en)
{
	u32 umac_base = params->port ? GRCBASE_UMAC1 : GRCBASE_UMAC0;
	u32 val;
	struct bnx2x *bp = params->bp;
	if (!(REG_RD(bp, MISC_REG_RESET_REG_2) &
		   (MISC_REGISTERS_RESET_REG_2_UMAC0 << params->port)))
		return;
	val = REG_RD(bp, umac_base + UMAC_REG_COMMAND_CONFIG);
	if (en)
		val |= (UMAC_COMMAND_CONFIG_REG_TX_ENA |
			UMAC_COMMAND_CONFIG_REG_RX_ENA);
	else
		val &= ~(UMAC_COMMAND_CONFIG_REG_TX_ENA |
			 UMAC_COMMAND_CONFIG_REG_RX_ENA);
	/* Disable RX and TX */
	REG_WR(bp, umac_base + UMAC_REG_COMMAND_CONFIG, val);
}