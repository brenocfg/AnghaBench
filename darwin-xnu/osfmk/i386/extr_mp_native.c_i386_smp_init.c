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
typedef  int /*<<< orphan*/  i386_intr_func_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  install_real_mode_bootstrap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapic_configure () ; 
 int /*<<< orphan*/  lapic_init () ; 
 int /*<<< orphan*/  lapic_probe () ; 
 int /*<<< orphan*/  lapic_set_intr_func (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slave_pstart ; 

boolean_t
i386_smp_init(int nmi_vector, i386_intr_func_t nmi_handler, int ipi_vector, i386_intr_func_t ipi_handler)
{
	/* Local APIC? */
	if (!lapic_probe())
		return FALSE;

	lapic_init();
	lapic_configure();
	lapic_set_intr_func(nmi_vector,  nmi_handler);
	lapic_set_intr_func(ipi_vector, ipi_handler);

	install_real_mode_bootstrap(slave_pstart);

	return TRUE;
}