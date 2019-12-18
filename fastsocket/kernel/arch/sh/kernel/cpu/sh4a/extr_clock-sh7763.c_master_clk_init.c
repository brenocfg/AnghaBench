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
struct clk {int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRQCR ; 
 int ctrl_inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * p0fc_divisors ; 

__attribute__((used)) static void master_clk_init(struct clk *clk)
{
	clk->rate *= p0fc_divisors[(ctrl_inl(FRQCR) >> 4) & 0x07];
}