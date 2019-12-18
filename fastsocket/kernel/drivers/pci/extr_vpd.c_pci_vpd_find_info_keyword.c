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
typedef  char u8 ;

/* Variables and functions */
 int ENOENT ; 
 int PCI_VPD_INFO_FLD_HDR_SIZE ; 
 scalar_t__ pci_vpd_info_field_size (char const*) ; 

int pci_vpd_find_info_keyword(const u8 *buf, unsigned int off,
			      unsigned int len, const char *kw)
{
	int i;

	for (i = off; i + PCI_VPD_INFO_FLD_HDR_SIZE <= off + len;) {
		if (buf[i + 0] == kw[0] &&
		    buf[i + 1] == kw[1])
			return i;

		i += PCI_VPD_INFO_FLD_HDR_SIZE +
		pci_vpd_info_field_size(&buf[i]);
	}

	return -ENOENT;
}