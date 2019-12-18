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
struct pci_driver {int dummy; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct drv_dev_and_id {struct pci_device_id const* member_2; struct pci_dev* member_1; struct pci_driver* member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_online_mask ; 
 int cpumask_any_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of_node (int) ; 
 int dev_to_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int local_pci_probe (struct drv_dev_and_id*) ; 
 int nr_cpu_ids ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int work_on_cpu (int,int (*) (struct drv_dev_and_id*),struct drv_dev_and_id*) ; 

__attribute__((used)) static int pci_call_probe(struct pci_driver *drv, struct pci_dev *dev,
			  const struct pci_device_id *id)
{
	int error, node;
	struct drv_dev_and_id ddi = { drv, dev, id };

	/* Execute driver initialization on node where the device's
	   bus is attached to.  This way the driver likely allocates
	   its local memory on the right node without any need to
	   change it. */
	node = dev_to_node(&dev->dev);
	if (node >= 0) {
		int cpu;

		get_online_cpus();
		cpu = cpumask_any_and(cpumask_of_node(node), cpu_online_mask);
		if (cpu < nr_cpu_ids)
			error = work_on_cpu(cpu, local_pci_probe, &ddi);
		else
			error = local_pci_probe(&ddi);
		put_online_cpus();
	} else
		error = local_pci_probe(&ddi);
	return error;
}