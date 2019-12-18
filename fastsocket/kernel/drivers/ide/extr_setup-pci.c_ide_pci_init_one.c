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
struct pci_dev {int dummy; } ;
struct ide_port_info {int dummy; } ;

/* Variables and functions */
 int ide_pci_init_two (struct pci_dev*,int /*<<< orphan*/ *,struct ide_port_info const*,void*) ; 

int ide_pci_init_one(struct pci_dev *dev, const struct ide_port_info *d,
		     void *priv)
{
	return ide_pci_init_two(dev, NULL, d, priv);
}