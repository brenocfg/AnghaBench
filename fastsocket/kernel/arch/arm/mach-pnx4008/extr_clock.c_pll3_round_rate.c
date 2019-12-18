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
typedef  int u32 ;
struct clk {int dummy; } ;

/* Variables and functions */
 int CLK_RATE_13MHZ ; 
 int CLK_RATE_208MHZ ; 

__attribute__((used)) static u32 pll3_round_rate(struct clk *clk, u32 rate)
{
	if (rate > CLK_RATE_208MHZ)
		rate = CLK_RATE_208MHZ;
	return (rate - rate % CLK_RATE_13MHZ);
}