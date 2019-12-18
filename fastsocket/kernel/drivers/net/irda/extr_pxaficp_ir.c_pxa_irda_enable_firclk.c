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
struct pxa_irda {int /*<<< orphan*/  fir_clk; int /*<<< orphan*/  cur_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void pxa_irda_enable_firclk(struct pxa_irda *si)
{
	si->cur_clk = si->fir_clk;
	clk_enable(si->fir_clk);
}