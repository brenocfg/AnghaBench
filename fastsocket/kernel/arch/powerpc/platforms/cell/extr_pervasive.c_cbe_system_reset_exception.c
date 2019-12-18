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
struct pt_regs {int msr; } ;

/* Variables and functions */
#define  SRR1_WAKEDEC 132 
#define  SRR1_WAKEEE 131 
 int SRR1_WAKEMASK ; 
#define  SRR1_WAKEMT 130 
#define  SRR1_WAKESYSERR 129 
#define  SRR1_WAKETHERM 128 
 int cbe_sysreset_hack () ; 
 int /*<<< orphan*/  cbe_system_error_exception (struct pt_regs*) ; 
 int /*<<< orphan*/  cbe_thermal_exception (struct pt_regs*) ; 
 int /*<<< orphan*/  do_IRQ (struct pt_regs*) ; 
 int /*<<< orphan*/  timer_interrupt (struct pt_regs*) ; 

__attribute__((used)) static int cbe_system_reset_exception(struct pt_regs *regs)
{
	switch (regs->msr & SRR1_WAKEMASK) {
	case SRR1_WAKEEE:
		do_IRQ(regs);
		break;
	case SRR1_WAKEDEC:
		timer_interrupt(regs);
		break;
	case SRR1_WAKEMT:
		return cbe_sysreset_hack();
#ifdef CONFIG_CBE_RAS
	case SRR1_WAKESYSERR:
		cbe_system_error_exception(regs);
		break;
	case SRR1_WAKETHERM:
		cbe_thermal_exception(regs);
		break;
#endif /* CONFIG_CBE_RAS */
	default:
		/* do system reset */
		return 0;
	}
	/* everything handled */
	return 1;
}