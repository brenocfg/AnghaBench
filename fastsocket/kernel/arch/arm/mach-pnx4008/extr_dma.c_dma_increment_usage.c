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
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 struct clk* clk_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  clk_set_rate (struct clk*,int) ; 
 int /*<<< orphan*/  dma_channels_requested ; 
 int /*<<< orphan*/  pnx4008_config_dma (int,int,int) ; 

__attribute__((used)) static inline void dma_increment_usage(void)
{
	if (!dma_channels_requested++) {
		struct clk *clk = clk_get(0, "dma_ck");
		if (!IS_ERR(clk)) {
			clk_set_rate(clk, 1);
			clk_put(clk);
		}
		pnx4008_config_dma(-1, -1, 1);
	}
}