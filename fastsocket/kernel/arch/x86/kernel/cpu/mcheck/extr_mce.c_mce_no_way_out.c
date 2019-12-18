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
struct mce {int status; } ;

/* Variables and functions */
 scalar_t__ MCE_PANIC_SEVERITY ; 
 int MCI_STATUS_VAL ; 
 int /*<<< orphan*/  MSR_IA32_MCx_STATUS (int) ; 
 int /*<<< orphan*/  __set_bit (int,unsigned long*) ; 
 int banks ; 
 int mce_rdmsrl (int /*<<< orphan*/ ) ; 
 scalar_t__ mce_severity (struct mce*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  quirk_no_way_out (int,struct mce*,struct pt_regs*) ; 
 int /*<<< orphan*/  tolerant ; 

__attribute__((used)) static int mce_no_way_out(struct mce *m, char **msg, unsigned long *validp,
			  struct pt_regs *regs)
{
	int i, ret = 0;

	for (i = 0; i < banks; i++) {
		m->status = mce_rdmsrl(MSR_IA32_MCx_STATUS(i));
		if (m->status & MCI_STATUS_VAL) {
			__set_bit(i, validp);
			if (quirk_no_way_out)
				quirk_no_way_out(i, m, regs);
		}
		if (mce_severity(m, tolerant, msg) >= MCE_PANIC_SEVERITY)
			ret = 1;
	}
	return ret;
}