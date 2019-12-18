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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct link_params {int port; struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ GRCBASE_UMAC0 ; 
 scalar_t__ GRCBASE_UMAC1 ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 scalar_t__ NIG_REG_EGRESS_EMAC0_PORT ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,scalar_t__,int) ; 
 scalar_t__ UMAC_REG_MAXFR ; 
 int /*<<< orphan*/  bnx2x_cl22_read (struct bnx2x*,struct bnx2x_phy*,int,int*) ; 
 int /*<<< orphan*/  bnx2x_cl22_write (struct bnx2x*,struct bnx2x_phy*,int,int) ; 

__attribute__((used)) static void bnx2x_54618se_config_loopback(struct bnx2x_phy *phy,
					  struct link_params *params)
{
	struct bnx2x *bp = params->bp;
	u16 val;
	u32 umac_base = params->port ? GRCBASE_UMAC1 : GRCBASE_UMAC0;

	DP(NETIF_MSG_LINK, "2PMA/PMD ext_phy_loopback: 54618se\n");

	/* Enable master/slave manual mmode and set to master */
	/* mii write 9 [bits set 11 12] */
	bnx2x_cl22_write(bp, phy, 0x09, 3<<11);

	/* forced 1G and disable autoneg */
	/* set val [mii read 0] */
	/* set val [expr $val & [bits clear 6 12 13]] */
	/* set val [expr $val | [bits set 6 8]] */
	/* mii write 0 $val */
	bnx2x_cl22_read(bp, phy, 0x00, &val);
	val &= ~((1<<6) | (1<<12) | (1<<13));
	val |= (1<<6) | (1<<8);
	bnx2x_cl22_write(bp, phy, 0x00, val);

	/* Set external loopback and Tx using 6dB coding */
	/* mii write 0x18 7 */
	/* set val [mii read 0x18] */
	/* mii write 0x18 [expr $val | [bits set 10 15]] */
	bnx2x_cl22_write(bp, phy, 0x18, 7);
	bnx2x_cl22_read(bp, phy, 0x18, &val);
	bnx2x_cl22_write(bp, phy, 0x18, val | (1<<10) | (1<<15));

	/* This register opens the gate for the UMAC despite its name */
	REG_WR(bp, NIG_REG_EGRESS_EMAC0_PORT + params->port*4, 1);

	/* Maximum Frame Length (RW). Defines a 14-Bit maximum frame
	 * length used by the MAC receive logic to check frames.
	 */
	REG_WR(bp, umac_base + UMAC_REG_MAXFR, 0x2710);
}