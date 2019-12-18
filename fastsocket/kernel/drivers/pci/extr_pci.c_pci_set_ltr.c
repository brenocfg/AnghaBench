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

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_LTR ; 
 scalar_t__ PCI_LTR_MAX_NOSNOOP_LAT ; 
 scalar_t__ PCI_LTR_MAX_SNOOP_LAT ; 
 int PCI_LTR_SCALE_MASK ; 
 int PCI_LTR_SCALE_SHIFT ; 
 int PCI_LTR_VALUE_MASK ; 
 int __pci_ltr_scale (int*) ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_ltr_supported (struct pci_dev*) ; 
 int pci_write_config_word (struct pci_dev*,scalar_t__,int) ; 

int pci_set_ltr(struct pci_dev *dev, int snoop_lat_ns, int nosnoop_lat_ns)
{
	int pos, ret, snoop_scale, nosnoop_scale;
	u16 val;

	if (!pci_ltr_supported(dev))
		return -ENOTSUPP;

	snoop_scale = __pci_ltr_scale(&snoop_lat_ns);
	nosnoop_scale = __pci_ltr_scale(&nosnoop_lat_ns);

	if (snoop_lat_ns > PCI_LTR_VALUE_MASK ||
	    nosnoop_lat_ns > PCI_LTR_VALUE_MASK)
		return -EINVAL;

	if ((snoop_scale > (PCI_LTR_SCALE_MASK >> PCI_LTR_SCALE_SHIFT)) ||
	    (nosnoop_scale > (PCI_LTR_SCALE_MASK >> PCI_LTR_SCALE_SHIFT)))
		return -EINVAL;

	pos = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_LTR);
	if (!pos)
		return -ENOTSUPP;

	val = (snoop_scale << PCI_LTR_SCALE_SHIFT) | snoop_lat_ns;
	ret = pci_write_config_word(dev, pos + PCI_LTR_MAX_SNOOP_LAT, val);
	if (ret != 4)
		return -EIO;

	val = (nosnoop_scale << PCI_LTR_SCALE_SHIFT) | nosnoop_lat_ns;
	ret = pci_write_config_word(dev, pos + PCI_LTR_MAX_NOSNOOP_LAT, val);
	if (ret != 4)
		return -EIO;

	return 0;
}