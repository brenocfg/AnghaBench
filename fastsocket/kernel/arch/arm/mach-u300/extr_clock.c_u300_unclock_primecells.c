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

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intcon_clk ; 
 int /*<<< orphan*/  mmcsd_clk ; 
 int /*<<< orphan*/  spi_clk ; 
 int /*<<< orphan*/  uart1_clk ; 
 int /*<<< orphan*/  uart_clk ; 

void u300_unclock_primecells(void)
{

	clk_disable(&intcon_clk);
	clk_disable(&uart_clk);
#ifdef CONFIG_MACH_U300_BS335
	clk_disable(&uart1_clk);
#endif
	clk_disable(&spi_clk);
	clk_disable(&mmcsd_clk);

}