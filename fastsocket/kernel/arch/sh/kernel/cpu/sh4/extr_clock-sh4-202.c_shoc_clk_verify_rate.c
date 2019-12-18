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
 struct clk* clk_get (int /*<<< orphan*/ *,char*) ; 
 unsigned long clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 

__attribute__((used)) static int shoc_clk_verify_rate(struct clk *clk, unsigned long rate)
{
	struct clk *bclk = clk_get(NULL, "bus_clk");
	unsigned long bclk_rate = clk_get_rate(bclk);

	clk_put(bclk);

	if (rate > bclk_rate)
		return 1;
	if (rate > 66000000)
		return 1;

	return 0;
}