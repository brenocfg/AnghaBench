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
struct pt_regs {int dummy; } ;
struct op_counter_config {int dummy; } ;

/* Variables and functions */
 scalar_t__ PPU_PROFILING ; 
 int /*<<< orphan*/  cell_handle_interrupt_ppu (struct pt_regs*,struct op_counter_config*) ; 
 int /*<<< orphan*/  cell_handle_interrupt_spu (struct pt_regs*,struct op_counter_config*) ; 
 scalar_t__ profiling_mode ; 

__attribute__((used)) static void cell_handle_interrupt(struct pt_regs *regs,
				  struct op_counter_config *ctr)
{
	if (profiling_mode == PPU_PROFILING)
		cell_handle_interrupt_ppu(regs, ctr);
	else
		cell_handle_interrupt_spu(regs, ctr);
}