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
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  subordinate; } ;
struct aer_err_info {int /*<<< orphan*/  id; scalar_t__ error_dev_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int find_device_iter (struct pci_dev*,struct aer_err_info*) ; 
 int /*<<< orphan*/  pci_walk_bus (int /*<<< orphan*/ ,int (*) (struct pci_dev*,struct aer_err_info*),struct aer_err_info*) ; 

__attribute__((used)) static bool find_source_device(struct pci_dev *parent,
		struct aer_err_info *e_info)
{
	struct pci_dev *dev = parent;
	int result;

	/* Must reset in this function */
	e_info->error_dev_num = 0;

	/* Is Root Port an agent that sends error message? */
	result = find_device_iter(dev, e_info);
	if (result)
		return true;

	pci_walk_bus(parent->subordinate, find_device_iter, e_info);

	if (!e_info->error_dev_num) {
		dev_printk(KERN_DEBUG, &parent->dev,
				"can't find device of ID%04x\n",
				e_info->id);
		return false;
	}
	return true;
}