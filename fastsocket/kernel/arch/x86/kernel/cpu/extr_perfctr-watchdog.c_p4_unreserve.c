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
 int /*<<< orphan*/  release_evntsel_nmi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_perfctr_nmi (int /*<<< orphan*/ ) ; 
 int smp_num_siblings ; 

__attribute__((used)) static void p4_unreserve(void)
{
#ifdef CONFIG_SMP
	if (smp_num_siblings > 1)
		release_perfctr_nmi(MSR_P4_IQ_PERFCTR1);
#endif
	release_evntsel_nmi(MSR_P4_CRU_ESCR0);
	release_perfctr_nmi(MSR_P4_IQ_PERFCTR0);
}