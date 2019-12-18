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
 int /*<<< orphan*/  local_irq_restore (int /*<<< orphan*/ ) ; 
 unsigned int paravirt_get_lazy_mode () ; 
 int /*<<< orphan*/  percpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_mc_flush () ; 
 int /*<<< orphan*/  xen_mc_irq_flags ; 

__attribute__((used)) static inline void xen_mc_issue(unsigned mode)
{
	if ((paravirt_get_lazy_mode() & mode) == 0)
		xen_mc_flush();

	/* restore flags saved in xen_mc_batch */
	local_irq_restore(percpu_read(xen_mc_irq_flags));
}