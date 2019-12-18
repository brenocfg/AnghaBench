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
struct pci_dev {int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* pci_busdev_to_OF_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct device_node*
pci_device_to_OF_node(struct pci_dev *dev)
{
	return pci_busdev_to_OF_node(dev->bus, dev->devfn);
}