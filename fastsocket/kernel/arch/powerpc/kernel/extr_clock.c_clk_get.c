#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {struct clk* (* clk_get ) (struct device*,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 TYPE_1__ clk_functions ; 
 struct clk* stub1 (struct device*,char const*) ; 

struct clk *clk_get(struct device *dev, const char *id)
{
	if (clk_functions.clk_get)
		return clk_functions.clk_get(dev, id);
	return ERR_PTR(-ENOSYS);
}