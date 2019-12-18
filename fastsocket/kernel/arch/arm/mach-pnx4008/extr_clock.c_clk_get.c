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
struct clk {int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct clk**) ; 
 int /*<<< orphan*/  ENOENT ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_lock () ; 
 int /*<<< orphan*/  clock_unlock () ; 
 struct clk** onchip_clks ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ try_module_get (int /*<<< orphan*/ ) ; 

struct clk *clk_get(struct device *dev, const char *id)
{
	struct clk *clk = ERR_PTR(-ENOENT);
	struct clk **clkp;

	clock_lock();
	for (clkp = onchip_clks; clkp < onchip_clks + ARRAY_SIZE(onchip_clks);
	     clkp++) {
		if (strcmp(id, (*clkp)->name) == 0
		    && try_module_get((*clkp)->owner)) {
			clk = (*clkp);
			break;
		}
	}
	clock_unlock();

	return clk;
}