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
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct AdapterControlBlock {int dev_id; int /*<<< orphan*/  adapter_type; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACB_ADAPTER_TYPE_A ; 
 int /*<<< orphan*/  ACB_ADAPTER_TYPE_B ; 
 int /*<<< orphan*/  ACB_ADAPTER_TYPE_C ; 
 int /*<<< orphan*/  PCI_DEVICE_ID ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void arcmsr_define_adapter_type(struct AdapterControlBlock *acb)
{
	struct pci_dev *pdev = acb->pdev;
	u16 dev_id;
	pci_read_config_word(pdev, PCI_DEVICE_ID, &dev_id);
	acb->dev_id = dev_id;
	switch (dev_id) {
	case 0x1880: {
		acb->adapter_type = ACB_ADAPTER_TYPE_C;
		}
		break;
	case 0x1201: {
		acb->adapter_type = ACB_ADAPTER_TYPE_B;
		}
		break;

	default: acb->adapter_type = ACB_ADAPTER_TYPE_A;
	}
}