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
struct clk {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long _clk_ssix_recalc(struct clk *clk, unsigned long pdf)
{
	unsigned long parent_rate;

	parent_rate = clk_get_rate(clk->parent);

	pdf = (pdf < 2) ? 124UL : pdf;  /* MX21 & MX27 TO1 */

	return 2UL * parent_rate / pdf;
}