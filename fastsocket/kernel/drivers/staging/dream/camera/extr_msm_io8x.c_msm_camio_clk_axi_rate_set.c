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
struct clk {int dummy; } ;

/* Variables and functions */
 struct clk* camio_vfe_axi_clk ; 
 int /*<<< orphan*/  clk_set_rate (struct clk*,int) ; 

void msm_camio_clk_axi_rate_set(int rate)
{
	struct clk *clk = camio_vfe_axi_clk;
	/* todo: check return */
	clk_set_rate(clk, rate);
}