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
struct clk {int flags; int /*<<< orphan*/  (* set_rate ) (struct clk*,int /*<<< orphan*/ ) ;scalar_t__ rate; } ;

/* Variables and functions */
 int FIXED_RATE ; 
 int /*<<< orphan*/  stub1 (struct clk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void local_clk_disable(struct clk *clk)
{
	if (!(clk->flags & FIXED_RATE) && clk->rate && clk->set_rate)
		clk->set_rate(clk, 0);
}