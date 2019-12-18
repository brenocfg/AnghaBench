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
struct clk {int flags; int /*<<< orphan*/  lpsc; int /*<<< orphan*/  psc_ctlr; int /*<<< orphan*/  usecount; struct clk* parent; } ;

/* Variables and functions */
 int CLK_PSC ; 
 int /*<<< orphan*/  davinci_psc_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  psc_domain (struct clk*) ; 

__attribute__((used)) static void __clk_enable(struct clk *clk)
{
	if (clk->parent)
		__clk_enable(clk->parent);
	if (clk->usecount++ == 0 && (clk->flags & CLK_PSC))
		davinci_psc_config(psc_domain(clk), clk->psc_ctlr,
				clk->lpsc, 1);
}