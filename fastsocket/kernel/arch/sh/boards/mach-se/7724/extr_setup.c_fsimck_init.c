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
struct clk {int /*<<< orphan*/  enable_reg; } ;

/* Variables and functions */
 int ctrl_inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_outl (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsimck_init(struct clk *clk)
{
	u32 status = ctrl_inl(clk->enable_reg);

	/* use external clock */
	status &= ~0x000000ff;
	status |= 0x00000080;
	ctrl_outl(status, clk->enable_reg);
}