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
struct sn_irq_info {int irq_slice; int irq_cpuid; size_t irq_irq; int /*<<< orphan*/  list; int /*<<< orphan*/  irq_pciioinfo; int /*<<< orphan*/  irq_nasid; } ;
struct pci_dev {int dummy; } ;
struct irq_desc {int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  nasid_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_AFFINITY_SET ; 
 int /*<<< orphan*/  SN_PCIDEV_INFO (struct pci_dev*) ; 
 int cpu_physical_id (int) ; 
 struct irq_desc* irq_to_desc (size_t) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nasid_slice_to_cpuid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_dev_get (struct pci_dev*) ; 
 int /*<<< orphan*/  register_intr_pda (struct sn_irq_info*) ; 
 int /*<<< orphan*/  reserve_irq_vector (size_t) ; 
 int /*<<< orphan*/  set_irq_affinity_info (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sn_irq_info_lock ; 
 int /*<<< orphan*/ * sn_irq_lh ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void sn_irq_fixup(struct pci_dev *pci_dev, struct sn_irq_info *sn_irq_info)
{
	nasid_t nasid = sn_irq_info->irq_nasid;
	int slice = sn_irq_info->irq_slice;
	int cpu = nasid_slice_to_cpuid(nasid, slice);
#ifdef CONFIG_SMP
	int cpuphys;
	struct irq_desc *desc;
#endif

	pci_dev_get(pci_dev);
	sn_irq_info->irq_cpuid = cpu;
	sn_irq_info->irq_pciioinfo = SN_PCIDEV_INFO(pci_dev);

	/* link it into the sn_irq[irq] list */
	spin_lock(&sn_irq_info_lock);
	list_add_rcu(&sn_irq_info->list, sn_irq_lh[sn_irq_info->irq_irq]);
	reserve_irq_vector(sn_irq_info->irq_irq);
	spin_unlock(&sn_irq_info_lock);

	register_intr_pda(sn_irq_info);
#ifdef CONFIG_SMP
	cpuphys = cpu_physical_id(cpu);
	set_irq_affinity_info(sn_irq_info->irq_irq, cpuphys, 0);
	desc = irq_to_desc(sn_irq_info->irq_irq);
	/*
	 * Affinity was set by the PROM, prevent it from
	 * being reset by the request_irq() path.
	 */
	desc->status |= IRQ_AFFINITY_SET;
#endif
}