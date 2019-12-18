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
typedef  int u16 ;
struct sky2_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMAC_IRQ_MSK ; 
 int /*<<< orphan*/  GM_MC_ADDR_H1 ; 
 int /*<<< orphan*/  GM_MC_ADDR_H2 ; 
 int /*<<< orphan*/  GM_MC_ADDR_H3 ; 
 int /*<<< orphan*/  GM_MC_ADDR_H4 ; 
 int GM_RXCR_MCF_ENA ; 
 int GM_RXCR_UCF_ENA ; 
 int /*<<< orphan*/  GM_RX_CTRL ; 
 int /*<<< orphan*/  SK_REG (unsigned int,int /*<<< orphan*/ ) ; 
 int gma_read16 (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_write16 (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sky2_gmac_reset(struct sky2_hw *hw, unsigned port)
{
	u16 reg;

	/* disable all GMAC IRQ's */
	sky2_write8(hw, SK_REG(port, GMAC_IRQ_MSK), 0);

	gma_write16(hw, port, GM_MC_ADDR_H1, 0);	/* clear MC hash */
	gma_write16(hw, port, GM_MC_ADDR_H2, 0);
	gma_write16(hw, port, GM_MC_ADDR_H3, 0);
	gma_write16(hw, port, GM_MC_ADDR_H4, 0);

	reg = gma_read16(hw, port, GM_RX_CTRL);
	reg |= GM_RXCR_UCF_ENA | GM_RXCR_MCF_ENA;
	gma_write16(hw, port, GM_RX_CTRL, reg);
}