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

/* Variables and functions */
 unsigned long ESCAPE_CODE ; 
 int /*<<< orphan*/  __oprofile_add_ext_sample (unsigned long,struct pt_regs* const,unsigned long,int) ; 
 scalar_t__ likely (struct pt_regs* const) ; 
 unsigned long profile_pc (struct pt_regs* const) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs* const) ; 

void oprofile_add_sample(struct pt_regs * const regs, unsigned long event)
{
	int is_kernel;
	unsigned long pc;

	if (likely(regs)) {
		is_kernel = !user_mode(regs);
		pc = profile_pc(regs);
	} else {
		is_kernel = 0;    /* This value will not be used */
		pc = ESCAPE_CODE; /* as this causes an early return. */
	}

	__oprofile_add_ext_sample(pc, regs, event, is_kernel);
}