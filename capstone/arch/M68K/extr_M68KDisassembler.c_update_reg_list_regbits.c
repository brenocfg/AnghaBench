#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  m68k_info ;
struct TYPE_3__ {int register_bits; } ;
typedef  TYPE_1__ cs_m68k_op ;

/* Variables and functions */
 int /*<<< orphan*/  M68K_REG_A0 ; 
 int /*<<< orphan*/  M68K_REG_D0 ; 
 int /*<<< orphan*/  M68K_REG_FP0 ; 
 int /*<<< orphan*/  update_bits_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void update_reg_list_regbits(m68k_info *info, cs_m68k_op *op, int write)
{
	uint32_t bits = op->register_bits;
	update_bits_range(info, M68K_REG_D0, bits & 0xff, write);
	update_bits_range(info, M68K_REG_A0, (bits >> 8) & 0xff, write);
	update_bits_range(info, M68K_REG_FP0, (bits >> 16) & 0xff, write);
}