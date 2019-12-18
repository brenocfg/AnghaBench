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
 scalar_t__ CHIP_REV_2_0 ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 scalar_t__ mx27_revision () ; 

__attribute__((used)) static unsigned long get_rate_ssix(struct clk *clk, unsigned long pdf)
{
	unsigned long parent_rate;

	parent_rate = clk_get_rate(clk->parent);

	if (mx27_revision() >= CHIP_REV_2_0)
		pdf += 4;  /* MX27 TO2+ */
	else
		pdf = (pdf < 2) ? 124UL : pdf;  /* MX21 & MX27 TO1 */

	return 2UL * parent_rate / pdf;
}