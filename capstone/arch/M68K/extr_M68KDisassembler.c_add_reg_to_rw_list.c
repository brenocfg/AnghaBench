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
typedef  void* uint16_t ;
typedef  scalar_t__ m68k_reg ;
struct TYPE_3__ {size_t regs_write_count; size_t regs_read_count; void** regs_read; void** regs_write; } ;
typedef  TYPE_1__ m68k_info ;

/* Variables and functions */
 scalar_t__ M68K_REG_INVALID ; 
 scalar_t__ exists_reg_list (void**,size_t,scalar_t__) ; 

__attribute__((used)) static void add_reg_to_rw_list(m68k_info *info, m68k_reg reg, int write)
{
	if (reg == M68K_REG_INVALID)
		return;

	if (write)
	{
		if (exists_reg_list(info->regs_write, info->regs_write_count, reg))
			return;

		info->regs_write[info->regs_write_count] = (uint16_t)reg;
		info->regs_write_count++;
	}
	else
	{
		if (exists_reg_list(info->regs_read, info->regs_read_count, reg))
			return;

		info->regs_read[info->regs_read_count] = (uint16_t)reg;
		info->regs_read_count++;
	}
}