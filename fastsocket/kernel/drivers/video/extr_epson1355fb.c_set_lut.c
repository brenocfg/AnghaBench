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
typedef  int /*<<< orphan*/  u8 ;
struct epson1355_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_LUT_ADDR ; 
 int /*<<< orphan*/  REG_LUT_DATA ; 
 int /*<<< orphan*/  epson1355_write_reg (struct epson1355_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_lut(struct epson1355_par *par, u8 index, u8 r, u8 g, u8 b)
{
	epson1355_write_reg(par, index, REG_LUT_ADDR);
	epson1355_write_reg(par, r, REG_LUT_DATA);
	epson1355_write_reg(par, g, REG_LUT_DATA);
	epson1355_write_reg(par, b, REG_LUT_DATA);
}