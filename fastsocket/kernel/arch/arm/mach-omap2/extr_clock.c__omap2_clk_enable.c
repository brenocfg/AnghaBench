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
struct clk {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* enable ) (struct clk*) ;} ;

/* Variables and functions */
 int stub1 (struct clk*) ; 

__attribute__((used)) static int _omap2_clk_enable(struct clk *clk)
{
	return clk->ops->enable(clk);
}