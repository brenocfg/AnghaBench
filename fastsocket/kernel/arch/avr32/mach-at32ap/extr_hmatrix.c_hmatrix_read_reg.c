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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  __hmatrix_read_reg (unsigned long) ; 
 int /*<<< orphan*/  at32_hmatrix_clk ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ *) ; 

u32 hmatrix_read_reg(unsigned long offset)
{
	u32 value;

	clk_enable(&at32_hmatrix_clk);
	value = __hmatrix_read_reg(offset);
	clk_disable(&at32_hmatrix_clk);

	return value;
}