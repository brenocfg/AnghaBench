#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;
struct nouveau_bios {int* data; int size; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int nouveau_acpi_get_bios_chunk (int*,int,int) ; 
 int /*<<< orphan*/  nouveau_acpi_rom_supported (struct pci_dev*) ; 
 TYPE_1__* nv_device (struct nouveau_bios*) ; 
 scalar_t__ nvbios_checksum (int*,int) ; 

__attribute__((used)) static void
nouveau_bios_shadow_acpi(struct nouveau_bios *bios)
{
	struct pci_dev *pdev = nv_device(bios)->pdev;
	int ret, cnt, i;

	if (!nouveau_acpi_rom_supported(pdev)) {
		bios->data = NULL;
		return;
	}

	bios->size = 0;
	bios->data = kmalloc(4096, GFP_KERNEL);
	if (bios->data) {
		if (nouveau_acpi_get_bios_chunk(bios->data, 0, 4096) == 4096)
			bios->size = bios->data[2] * 512;
		kfree(bios->data);
	}

	if (!bios->size)
		return;

	bios->data = kmalloc(bios->size, GFP_KERNEL);
	if (bios->data) {
		/* disobey the acpi spec - much faster on at least w530 ... */
		ret = nouveau_acpi_get_bios_chunk(bios->data, 0, bios->size);
		if (ret != bios->size ||
		    nvbios_checksum(bios->data, bios->size)) {
			/* ... that didn't work, ok, i'll be good now */
			for (i = 0; i < bios->size; i += cnt) {
				cnt = min((bios->size - i), (u32)4096);
				ret = nouveau_acpi_get_bios_chunk(bios->data, i, cnt);
				if (ret != cnt)
					break;
			}
		}
	}
}