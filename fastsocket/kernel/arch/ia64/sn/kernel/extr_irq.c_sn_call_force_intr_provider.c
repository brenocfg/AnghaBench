#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sn_pcibus_provider {int /*<<< orphan*/  (* force_interrupt ) (struct sn_irq_info*) ;} ;
struct sn_irq_info {size_t irq_bridge_type; size_t irq_irq; } ;
struct TYPE_2__ {int status; } ;

/* Variables and functions */
 int IRQ_DISABLED ; 
 TYPE_1__* irq_desc ; 
 struct sn_pcibus_provider** sn_pci_provider ; 
 int /*<<< orphan*/  stub1 (struct sn_irq_info*) ; 

__attribute__((used)) static inline void
sn_call_force_intr_provider(struct sn_irq_info *sn_irq_info)
{
	struct sn_pcibus_provider *pci_provider;

	pci_provider = sn_pci_provider[sn_irq_info->irq_bridge_type];

	/* Don't force an interrupt if the irq has been disabled */
	if (!(irq_desc[sn_irq_info->irq_irq].status & IRQ_DISABLED) &&
	    pci_provider && pci_provider->force_interrupt)
		(*pci_provider->force_interrupt)(sn_irq_info);
}