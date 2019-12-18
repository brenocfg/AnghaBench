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
 unsigned long CCM_CSCR_IPDIV ; 
 unsigned long CCM_CSCR_IPDIV_OFFSET ; 
 unsigned long CSCR () ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long get_ipg_clk(struct clk *clk)
{
	unsigned long rate;
	unsigned long ipg_pdf;

	ipg_pdf = (CSCR() & CCM_CSCR_IPDIV) >> CCM_CSCR_IPDIV_OFFSET;

	rate = clk_get_rate(clk->parent);
	return rate / (ipg_pdf + 1);
}