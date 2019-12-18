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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARAVIRT_LAZY_CPU ; 
 unsigned long __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __va (unsigned long) ; 
 int /*<<< orphan*/  __xen_write_cr3 (int,unsigned long) ; 
 int /*<<< orphan*/  percpu_write (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  preemptible () ; 
 int /*<<< orphan*/  xen_cr3 ; 
 int /*<<< orphan*/ * xen_get_user_pgd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_mc_batch () ; 
 int /*<<< orphan*/  xen_mc_issue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xen_write_cr3(unsigned long cr3)
{
	BUG_ON(preemptible());

	xen_mc_batch();  /* disables interrupts */

	/* Update while interrupts are disabled, so its atomic with
	   respect to ipis */
	percpu_write(xen_cr3, cr3);

	__xen_write_cr3(true, cr3);

#ifdef CONFIG_X86_64
	{
		pgd_t *user_pgd = xen_get_user_pgd(__va(cr3));
		if (user_pgd)
			__xen_write_cr3(false, __pa(user_pgd));
		else
			__xen_write_cr3(false, 0);
	}
#endif

	xen_mc_issue(PARAVIRT_LAZY_CPU);  /* interrupts restored */
}