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
struct niu {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESR2_TI_PLL_RX_CFG_H (unsigned long) ; 
 int /*<<< orphan*/  ESR2_TI_PLL_RX_CFG_L (unsigned long) ; 
 int /*<<< orphan*/  NIU_ESR2_DEV_ADDR ; 
 int mdio_write (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int esr2_set_rx_cfg(struct niu *np, unsigned long channel, u32 val)
{
	int err;

	err = mdio_write(np, np->port, NIU_ESR2_DEV_ADDR,
			 ESR2_TI_PLL_RX_CFG_L(channel),
			 val & 0xffff);
	if (!err)
		err = mdio_write(np, np->port, NIU_ESR2_DEV_ADDR,
				 ESR2_TI_PLL_RX_CFG_H(channel),
				 val >> 16);
	return err;
}