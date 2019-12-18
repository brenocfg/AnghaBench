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
struct clk_lookup {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  clkdev_add (struct clk_lookup*) ; 
 struct clk_lookup* clkdev_alloc (struct clk*,int /*<<< orphan*/ *,char const*) ; 

int nmdk_clk_create(struct clk *clk, const char *dev_id)
{
	struct clk_lookup *clkdev;

	clkdev = clkdev_alloc(clk, NULL, dev_id);
	if (!clkdev)
		return -ENOMEM;
	clkdev_add(clkdev);
	return 0;
}