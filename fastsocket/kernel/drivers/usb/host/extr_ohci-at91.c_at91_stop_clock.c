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
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 scalar_t__ clocked ; 
 scalar_t__ cpu_is_at91sam9261 () ; 
 int /*<<< orphan*/  fclk ; 
 int /*<<< orphan*/  hclk ; 
 int /*<<< orphan*/  iclk ; 

__attribute__((used)) static void at91_stop_clock(void)
{
	clk_disable(fclk);
	clk_disable(iclk);
	if (cpu_is_at91sam9261())
		clk_disable(hclk);
	clocked = 0;
}