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
struct kvm_lapic_irq {int delivery_mode; } ;

/* Variables and functions */
 int APIC_DM_LOWEST ; 
 int IOSAPIC_DELIVERY_SHIFT ; 
 int IOSAPIC_LOWEST_PRIORITY ; 

__attribute__((used)) inline static bool kvm_is_dm_lowest_prio(struct kvm_lapic_irq *irq)
{
#ifdef CONFIG_IA64
	return irq->delivery_mode ==
		(IOSAPIC_LOWEST_PRIORITY << IOSAPIC_DELIVERY_SHIFT);
#else
	return irq->delivery_mode == APIC_DM_LOWEST;
#endif
}