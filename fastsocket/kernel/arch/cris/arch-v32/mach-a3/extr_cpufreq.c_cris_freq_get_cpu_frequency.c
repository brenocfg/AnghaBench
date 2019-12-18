#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pll; } ;
typedef  TYPE_1__ reg_clkgen_rw_clk_ctrl ;

/* Variables and functions */
 TYPE_1__ REG_RD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkgen ; 
 int /*<<< orphan*/  regi_clkgen ; 
 int /*<<< orphan*/  rw_clk_ctrl ; 

__attribute__((used)) static unsigned int cris_freq_get_cpu_frequency(unsigned int cpu)
{
	reg_clkgen_rw_clk_ctrl clk_ctrl;
	clk_ctrl = REG_RD(clkgen, regi_clkgen, rw_clk_ctrl);
	return clk_ctrl.pll ? 200000 : 6000;
}