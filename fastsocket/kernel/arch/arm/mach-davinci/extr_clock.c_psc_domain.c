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
struct clk {int flags; } ;

/* Variables and functions */
 int DAVINCI_GPSC_ARMDOMAIN ; 
 int DAVINCI_GPSC_DSPDOMAIN ; 
 int PSC_DSP ; 

__attribute__((used)) static unsigned psc_domain(struct clk *clk)
{
	return (clk->flags & PSC_DSP)
		? DAVINCI_GPSC_DSPDOMAIN
		: DAVINCI_GPSC_ARMDOMAIN;
}