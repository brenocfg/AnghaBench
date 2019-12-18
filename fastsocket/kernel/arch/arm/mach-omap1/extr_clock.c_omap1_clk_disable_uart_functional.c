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
struct uart_clk {int /*<<< orphan*/  sysc_addr; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap1_clk_disable_generic (struct clk*) ; 
 int omap_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap1_clk_disable_uart_functional(struct clk *clk)
{
	struct uart_clk *uclk;

	/* Set force idle acknowledgement mode */
	uclk = (struct uart_clk *)clk;
	omap_writeb((omap_readb(uclk->sysc_addr) & ~0x18), uclk->sysc_addr);

	omap1_clk_disable_generic(clk);
}