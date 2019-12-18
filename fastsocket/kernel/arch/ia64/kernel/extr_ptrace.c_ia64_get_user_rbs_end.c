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
struct task_struct {int dummy; } ;
struct pt_regs {unsigned long cr_ifs; int loadrs; scalar_t__ ar_bspstore; } ;

/* Variables and functions */
 int IA64_RBS_OFFSET ; 
 long ia64_rse_num_regs (unsigned long*,unsigned long*) ; 
 scalar_t__ ia64_rse_skip_regs (unsigned long*,long) ; 
 scalar_t__ in_syscall (struct pt_regs*) ; 

unsigned long
ia64_get_user_rbs_end (struct task_struct *child, struct pt_regs *pt,
		       unsigned long *cfmp)
{
	unsigned long *krbs, *bspstore, cfm = pt->cr_ifs;
	long ndirty;

	krbs = (unsigned long *) child + IA64_RBS_OFFSET/8;
	bspstore = (unsigned long *) pt->ar_bspstore;
	ndirty = ia64_rse_num_regs(krbs, krbs + (pt->loadrs >> 19));

	if (in_syscall(pt))
		ndirty += (cfm & 0x7f);
	else
		cfm &= ~(1UL << 63);	/* clear valid bit */

	if (cfmp)
		*cfmp = cfm;
	return (unsigned long) ia64_rse_skip_regs(bspstore, ndirty);
}