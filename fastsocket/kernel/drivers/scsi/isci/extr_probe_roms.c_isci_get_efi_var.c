#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  signature; } ;
struct isci_orom {TYPE_1__ hdr; } ;
struct isci_oem_hdr {int /*<<< orphan*/  sig; } ;
typedef  scalar_t__ efi_status_t ;
struct TYPE_4__ {scalar_t__ (* get_variable ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long*,scalar_t__*) ;} ;

/* Variables and functions */
 scalar_t__ EFI_NOT_FOUND ; 
 scalar_t__ EFI_SUCCESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ISCI_EFI_VENDOR_GUID ; 
 int /*<<< orphan*/  ISCI_OEM_SIG ; 
 int /*<<< orphan*/  ISCI_OEM_SIG_SIZE ; 
 int /*<<< orphan*/  ISCI_ROM_SIG ; 
 int /*<<< orphan*/  ISCI_ROM_SIG_SIZE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__* devm_kzalloc (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_2__* get_efi () ; 
 int /*<<< orphan*/  isci_efivar_name ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long*,scalar_t__*) ; 

struct isci_orom *isci_get_efi_var(struct pci_dev *pdev)
{
	efi_status_t status;
	struct isci_orom *rom;
	struct isci_oem_hdr *oem_hdr;
	u8 *tmp, sum;
	int j;
	unsigned long data_len;
	u8 *efi_data;
	u32 efi_attrib = 0;

	data_len = 1024;
	efi_data = devm_kzalloc(&pdev->dev, data_len, GFP_KERNEL);
	if (!efi_data) {
		dev_warn(&pdev->dev,
			 "Unable to allocate memory for EFI data\n");
		return NULL;
	}

	rom = (struct isci_orom *)(efi_data + sizeof(struct isci_oem_hdr));

	if (get_efi())
		status = get_efi()->get_variable(isci_efivar_name,
						 &ISCI_EFI_VENDOR_GUID,
						 &efi_attrib,
						 &data_len,
						 efi_data);
	else
		status = EFI_NOT_FOUND;

	if (status != EFI_SUCCESS) {
		dev_warn(&pdev->dev,
			 "Unable to obtain EFI var data for OEM parms\n");
		return NULL;
	}

	oem_hdr = (struct isci_oem_hdr *)efi_data;

	if (memcmp(oem_hdr->sig, ISCI_OEM_SIG, ISCI_OEM_SIG_SIZE) != 0) {
		dev_warn(&pdev->dev,
			 "Invalid OEM header signature\n");
		return NULL;
	}

	/* calculate checksum */
	tmp = (u8 *)efi_data;
	for (j = 0, sum = 0; j < (sizeof(*oem_hdr) + sizeof(*rom)); j++, tmp++)
		sum += *tmp;

	if (sum != 0) {
		dev_warn(&pdev->dev,
			 "OEM table checksum failed\n");
		return NULL;
	}

	if (memcmp(rom->hdr.signature,
		   ISCI_ROM_SIG,
		   ISCI_ROM_SIG_SIZE) != 0) {
		dev_warn(&pdev->dev,
			 "Invalid OEM table signature\n");
		return NULL;
	}

	return rom;
}