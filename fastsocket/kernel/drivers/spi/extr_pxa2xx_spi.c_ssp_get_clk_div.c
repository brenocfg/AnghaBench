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
struct ssp_device {scalar_t__ type; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 scalar_t__ PXA25x_SSP ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int ssp_get_clk_div(struct ssp_device *ssp, int rate)
{
	unsigned long ssp_clk = clk_get_rate(ssp->clk);

	if (ssp->type == PXA25x_SSP)
		return ((ssp_clk / (2 * rate) - 1) & 0xff) << 8;
	else
		return ((ssp_clk / rate - 1) & 0xfff) << 8;
}