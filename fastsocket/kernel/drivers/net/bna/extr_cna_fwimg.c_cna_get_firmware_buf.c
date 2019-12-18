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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {scalar_t__ device; } ;

/* Variables and functions */
 scalar_t__ BFA_PCI_DEVICE_ID_CT2 ; 
 int /*<<< orphan*/  CNA_FW_FILE_CT ; 
 int /*<<< orphan*/  CNA_FW_FILE_CT2 ; 
 scalar_t__ bfa_asic_id_ct (scalar_t__) ; 
 int /*<<< orphan*/ * bfi_image_ct2_cna ; 
 scalar_t__ bfi_image_ct2_cna_size ; 
 int /*<<< orphan*/ * bfi_image_ct_cna ; 
 scalar_t__ bfi_image_ct_cna_size ; 
 int /*<<< orphan*/  cna_read_firmware (struct pci_dev*,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ ) ; 

u32 *
cna_get_firmware_buf(struct pci_dev *pdev)
{
	if (pdev->device == BFA_PCI_DEVICE_ID_CT2) {
		if (bfi_image_ct2_cna_size == 0)
			cna_read_firmware(pdev, &bfi_image_ct2_cna,
				&bfi_image_ct2_cna_size, CNA_FW_FILE_CT2);
		return bfi_image_ct2_cna;
	} else if (bfa_asic_id_ct(pdev->device)) {
		if (bfi_image_ct_cna_size == 0)
			cna_read_firmware(pdev, &bfi_image_ct_cna,
				&bfi_image_ct_cna_size, CNA_FW_FILE_CT);
		return bfi_image_ct_cna;
	}

	return NULL;
}