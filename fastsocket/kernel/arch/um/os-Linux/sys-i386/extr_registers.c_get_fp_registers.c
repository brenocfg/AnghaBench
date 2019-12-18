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

/* Variables and functions */
 scalar_t__ have_fpx_regs ; 
 int save_fp_registers (int,unsigned long*) ; 
 int save_fpx_registers (int,unsigned long*) ; 

int get_fp_registers(int pid, unsigned long *regs)
{
	if (have_fpx_regs)
		return save_fpx_registers(pid, regs);
	else
		return save_fp_registers(pid, regs);
}