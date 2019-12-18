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
struct skge_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GM_MC_ADDR_H1 ; 
 int /*<<< orphan*/  GM_MC_ADDR_H2 ; 
 int /*<<< orphan*/  GM_MC_ADDR_H3 ; 
 int /*<<< orphan*/  GM_MC_ADDR_H4 ; 
 int GM_RXCR_MCF_ENA ; 
 int GM_RXCR_UCF_ENA ; 
 int /*<<< orphan*/  GM_RX_CTRL ; 
 int /*<<< orphan*/  PHY_MARV_INT_MASK ; 
 int /*<<< orphan*/  gm_phy_write (struct skge_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gma_read16 (struct skge_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_write16 (struct skge_hw*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void yukon_reset(struct skge_hw *hw, int port)
{
	gm_phy_write(hw, port, PHY_MARV_INT_MASK, 0);/* disable PHY IRQs */
	gma_write16(hw, port, GM_MC_ADDR_H1, 0);	/* clear MC hash */
	gma_write16(hw, port, GM_MC_ADDR_H2, 0);
	gma_write16(hw, port, GM_MC_ADDR_H3, 0);
	gma_write16(hw, port, GM_MC_ADDR_H4, 0);

	gma_write16(hw, port, GM_RX_CTRL,
			 gma_read16(hw, port, GM_RX_CTRL)
			 | GM_RXCR_UCF_ENA | GM_RXCR_MCF_ENA);
}