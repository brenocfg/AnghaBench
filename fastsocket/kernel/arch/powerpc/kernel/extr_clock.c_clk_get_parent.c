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
struct clk {int dummy; } ;
struct TYPE_2__ {struct clk* (* clk_get_parent ) (struct clk*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 TYPE_1__ clk_functions ; 
 struct clk* stub1 (struct clk*) ; 

struct clk *clk_get_parent(struct clk *clk)
{
	if (clk_functions.clk_get_parent)
		return clk_functions.clk_get_parent(clk);
	return ERR_PTR(-ENOSYS);
}