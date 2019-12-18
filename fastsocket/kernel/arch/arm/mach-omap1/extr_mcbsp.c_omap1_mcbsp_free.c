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
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 unsigned int OMAP_MCBSP1 ; 
 unsigned int OMAP_MCBSP3 ; 
 int /*<<< orphan*/  api_clk ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsp_clk ; 
 scalar_t__ dsp_use ; 
 int /*<<< orphan*/  omap_dsp_release_mem () ; 

__attribute__((used)) static void omap1_mcbsp_free(unsigned int id)
{
	if (id == OMAP_MCBSP1 || id == OMAP_MCBSP3) {
		if (--dsp_use == 0) {
			omap_dsp_release_mem();
			if (!IS_ERR(api_clk)) {
				clk_disable(api_clk);
				clk_put(api_clk);
			}
			if (!IS_ERR(dsp_clk)) {
				clk_disable(dsp_clk);
				clk_put(dsp_clk);
			}
		}
	}
}