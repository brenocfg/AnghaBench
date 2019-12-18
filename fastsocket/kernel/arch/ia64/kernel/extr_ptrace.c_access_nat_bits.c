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
struct unw_frame_info {int dummy; } ;
struct task_struct {int dummy; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNW_AR_UNAT ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 unsigned long ia64_get_scratch_nat_bits (struct pt_regs*,unsigned long) ; 
 unsigned long ia64_put_scratch_nat_bits (struct pt_regs*,unsigned long) ; 
 scalar_t__ unw_get_ar (struct unw_frame_info*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  unw_get_gr (struct unw_frame_info*,unsigned long,unsigned long*,char*) ; 
 scalar_t__ unw_set_ar (struct unw_frame_info*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  unw_set_gr (struct unw_frame_info*,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static int
access_nat_bits (struct task_struct *child, struct pt_regs *pt,
		 struct unw_frame_info *info,
		 unsigned long *data, int write_access)
{
	unsigned long regnum, nat_bits, scratch_unat, dummy = 0;
	char nat = 0;

	if (write_access) {
		nat_bits = *data;
		scratch_unat = ia64_put_scratch_nat_bits(pt, nat_bits);
		if (unw_set_ar(info, UNW_AR_UNAT, scratch_unat) < 0) {
			dprintk("ptrace: failed to set ar.unat\n");
			return -1;
		}
		for (regnum = 4; regnum <= 7; ++regnum) {
			unw_get_gr(info, regnum, &dummy, &nat);
			unw_set_gr(info, regnum, dummy,
				   (nat_bits >> regnum) & 1);
		}
	} else {
		if (unw_get_ar(info, UNW_AR_UNAT, &scratch_unat) < 0) {
			dprintk("ptrace: failed to read ar.unat\n");
			return -1;
		}
		nat_bits = ia64_get_scratch_nat_bits(pt, scratch_unat);
		for (regnum = 4; regnum <= 7; ++regnum) {
			unw_get_gr(info, regnum, &dummy, &nat);
			nat_bits |= (nat != 0) << regnum;
		}
		*data = nat_bits;
	}
	return 0;
}