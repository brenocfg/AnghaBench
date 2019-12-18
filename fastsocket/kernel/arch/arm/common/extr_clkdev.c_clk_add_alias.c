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
struct device {int dummy; } ;
struct clk_lookup {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 struct clk* clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  clkdev_add (struct clk_lookup*) ; 
 struct clk_lookup* clkdev_alloc (struct clk*,char const*,char const*) ; 

int clk_add_alias(const char *alias, const char *alias_dev_name, char *id,
	struct device *dev)
{
	struct clk *r = clk_get(dev, id);
	struct clk_lookup *l;

	if (IS_ERR(r))
		return PTR_ERR(r);

	l = clkdev_alloc(r, alias, alias_dev_name);
	clk_put(r);
	if (!l)
		return -ENODEV;
	clkdev_add(l);
	return 0;
}