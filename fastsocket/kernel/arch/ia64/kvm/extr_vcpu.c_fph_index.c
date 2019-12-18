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
struct kvm_pt_regs {int cr_ifs; } ;

/* Variables and functions */
 scalar_t__ IA64_FIRST_ROTATING_FR ; 
 unsigned long rotate_reg (int,unsigned long,scalar_t__) ; 

__attribute__((used)) static inline unsigned long fph_index(struct kvm_pt_regs *regs,
						long regnum)
{
	unsigned long rrb_fr = (regs->cr_ifs >> 25) & 0x7f;
	return rotate_reg(96, rrb_fr, (regnum - IA64_FIRST_ROTATING_FR));
}