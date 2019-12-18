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
struct skge_port {int port; struct skge_hw* hw; } ;
struct skge_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMAC_CTRL ; 
 int /*<<< orphan*/  GMAC_IRQ_MSK ; 
 int /*<<< orphan*/  GMC_RST_SET ; 
 int GM_GPCR_RX_ENA ; 
 int GM_GPCR_TX_ENA ; 
 int /*<<< orphan*/  GM_GP_CTRL ; 
 int /*<<< orphan*/  GPC_RST_SET ; 
 int /*<<< orphan*/  GPHY_CTRL ; 
 int /*<<< orphan*/  SK_REG (int,int /*<<< orphan*/ ) ; 
 int gma_read16 (struct skge_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_write16 (struct skge_hw*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skge_write8 (struct skge_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yukon_reset (struct skge_hw*,int) ; 
 int /*<<< orphan*/  yukon_suspend (struct skge_hw*,int) ; 

__attribute__((used)) static void yukon_stop(struct skge_port *skge)
{
	struct skge_hw *hw = skge->hw;
	int port = skge->port;

	skge_write8(hw, SK_REG(port, GMAC_IRQ_MSK), 0);
	yukon_reset(hw, port);

	gma_write16(hw, port, GM_GP_CTRL,
			 gma_read16(hw, port, GM_GP_CTRL)
			 & ~(GM_GPCR_TX_ENA|GM_GPCR_RX_ENA));
	gma_read16(hw, port, GM_GP_CTRL);

	yukon_suspend(hw, port);

	/* set GPHY Control reset */
	skge_write8(hw, SK_REG(port, GPHY_CTRL), GPC_RST_SET);
	skge_write8(hw, SK_REG(port, GMAC_CTRL), GMC_RST_SET);
}