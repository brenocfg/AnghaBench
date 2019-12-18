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
 int /*<<< orphan*/  MSR_P4_CRU_ESCR0 ; 
 int /*<<< orphan*/  MSR_P4_IQ_PERFCTR0 ; 
 int /*<<< orphan*/  MSR_P4_IQ_PERFCTR1 ; 
 int /*<<< orphan*/  release_perfctr_nmi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reserve_evntsel_nmi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reserve_perfctr_nmi (int /*<<< orphan*/ ) ; 
 int smp_num_siblings ; 

__attribute__((used)) static int p4_reserve(void)
{
	if (!reserve_perfctr_nmi(MSR_P4_IQ_PERFCTR0))
		return 0;
#ifdef CONFIG_SMP
	if (smp_num_siblings > 1 && !reserve_perfctr_nmi(MSR_P4_IQ_PERFCTR1))
		goto fail1;
#endif
	if (!reserve_evntsel_nmi(MSR_P4_CRU_ESCR0))
		goto fail2;
	/* RED-PEN why is ESCR1 not reserved here? */
	return 1;
 fail2:
#ifdef CONFIG_SMP
	if (smp_num_siblings > 1)
		release_perfctr_nmi(MSR_P4_IQ_PERFCTR1);
 fail1:
#endif
	release_perfctr_nmi(MSR_P4_IQ_PERFCTR0);
	return 0;
}