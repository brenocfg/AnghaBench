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
 int /*<<< orphan*/  HMATRIX_SFR (unsigned int) ; 
 int /*<<< orphan*/  __hmatrix_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __hmatrix_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at32_hmatrix_clk ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ *) ; 

void hmatrix_sfr_clear_bits(unsigned int slave_id, u32 mask)
{
	u32 value;

	clk_enable(&at32_hmatrix_clk);
	value = __hmatrix_read_reg(HMATRIX_SFR(slave_id));
	value &= ~mask;
	__hmatrix_write_reg(HMATRIX_SFR(slave_id), value);
	__hmatrix_read_reg(HMATRIX_SFR(slave_id));
	clk_disable(&at32_hmatrix_clk);
}