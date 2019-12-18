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
struct clk {int dummy; } ;

/* Variables and functions */
 int CCM_PCDR0_SSI1BAUDDIV_MASK ; 
 int CCM_PCDR0_SSI1BAUDDIV_OFFSET ; 
 int PCDR0 () ; 
 unsigned long _clk_ssix_recalc (struct clk*,int) ; 

__attribute__((used)) static unsigned long _clk_ssi1_recalc(struct clk *clk)
{
	return _clk_ssix_recalc(clk,
		(PCDR0() & CCM_PCDR0_SSI1BAUDDIV_MASK)
		>> CCM_PCDR0_SSI1BAUDDIV_OFFSET);
}