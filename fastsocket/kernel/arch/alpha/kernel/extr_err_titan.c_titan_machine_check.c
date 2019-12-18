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
typedef  int u64 ;
struct el_common {scalar_t__ sys_offset; } ;
struct el_TITAN_sysdata_mcheck {int c_dirx; } ;

/* Variables and functions */
 char* KERN_CRIT ; 
 scalar_t__ MCHK_DISPOSITION_DISMISS ; 
 unsigned long SCB_Q_SYSERR ; 
 unsigned long SCB_Q_SYSMCHK ; 
 int TITAN_MCHECK_INTERRUPT_MASK ; 
 scalar_t__ alpha_verbose_mcheck ; 
 int /*<<< orphan*/  dik_show_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  draina () ; 
 char* err_print_prefix ; 
 int /*<<< orphan*/  ev6_machine_check (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  get_irq_regs () ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  printk (char*,char*,char*,unsigned int,int) ; 
 scalar_t__ smp_processor_id () ; 
 int /*<<< orphan*/  titan_dispatch_irqs (int) ; 
 scalar_t__ titan_process_logout_frame (struct el_common*,scalar_t__) ; 
 int /*<<< orphan*/  wrmces (int) ; 

void
titan_machine_check(unsigned long vector, unsigned long la_ptr)
{
	struct el_common *mchk_header = (struct el_common *)la_ptr;
	struct el_TITAN_sysdata_mcheck *tmchk =
		(struct el_TITAN_sysdata_mcheck *)
		((unsigned long)mchk_header + mchk_header->sys_offset);
	u64 irqmask;

	/*
	 * Mask of Titan interrupt sources which are reported as machine checks
	 *
	 * 63 - CChip Error
	 * 62 - PChip 0 H_Error
	 * 61 - PChip 1 H_Error
	 * 60 - PChip 0 C_Error
	 * 59 - PChip 1 C_Error
	 */
#define TITAN_MCHECK_INTERRUPT_MASK	0xF800000000000000UL

	/*
	 * Sync the processor
	 */
	mb();
	draina();
	
	/*
	 * Only handle system errors here 
	 */
	if ((vector != SCB_Q_SYSMCHK) && (vector != SCB_Q_SYSERR)) {
		ev6_machine_check(vector, la_ptr);
		return;
	}

	/* 
	 * It's a system error, handle it here
	 *
	 * The PALcode has already cleared the error, so just parse it
	 */
	
	/* 
	 * Parse the logout frame without printing first. If the only error(s)
	 * found are classified as "dismissable", then just dismiss them and
	 * don't print any message
	 */
	if (titan_process_logout_frame(mchk_header, 0) != 
	    MCHK_DISPOSITION_DISMISS) {
		char *saved_err_prefix = err_print_prefix;
		err_print_prefix = KERN_CRIT;

		/*
		 * Either a nondismissable error was detected or no
		 * recognized error was detected  in the logout frame 
		 * -- report the error in either case
		 */
		printk("%s"
		       "*System %s Error (Vector 0x%x) reported on CPU %d:\n", 
		       err_print_prefix,
		       (vector == SCB_Q_SYSERR)?"Correctable":"Uncorrectable",
		       (unsigned int)vector, (int)smp_processor_id());
		
#ifdef CONFIG_VERBOSE_MCHECK
		titan_process_logout_frame(mchk_header, alpha_verbose_mcheck);
		if (alpha_verbose_mcheck)
			dik_show_regs(get_irq_regs(), NULL);
#endif /* CONFIG_VERBOSE_MCHECK */

		err_print_prefix = saved_err_prefix;

		/*
		 * Convert any pending interrupts which report as system
		 * machine checks to interrupts
		 */
		irqmask = tmchk->c_dirx & TITAN_MCHECK_INTERRUPT_MASK;
		titan_dispatch_irqs(irqmask);
	}	


	/* 
	 * Release the logout frame 
	 */
	wrmces(0x7);
	mb();
}