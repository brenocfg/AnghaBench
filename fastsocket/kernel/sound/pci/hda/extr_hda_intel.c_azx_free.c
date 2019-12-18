#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ area; } ;
struct azx {int init_failed; int num_streams; scalar_t__ irq; scalar_t__ fw; struct azx* azx_dev; int /*<<< orphan*/  pci; scalar_t__ region_requested; TYPE_1__ posbuf; TYPE_1__ rb; TYPE_1__ bdl; scalar_t__ remap_addr; scalar_t__ msi; scalar_t__ initialized; scalar_t__ vga_switcheroo_registered; scalar_t__ bus; scalar_t__ disabled; int /*<<< orphan*/  probe_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  azx_clear_irq_pending (struct azx*) ; 
 int /*<<< orphan*/  azx_del_card_list (struct azx*) ; 
 int /*<<< orphan*/  azx_notifier_unregister (struct azx*) ; 
 int /*<<< orphan*/  azx_stop_chip (struct azx*) ; 
 int /*<<< orphan*/  azx_stream_stop (struct azx*,struct azx*) ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,void*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct azx*) ; 
 int /*<<< orphan*/  mark_pages_wc (struct azx*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (scalar_t__) ; 
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_hda_unlock_devices (scalar_t__) ; 
 scalar_t__ use_vga_switcheroo (struct azx*) ; 
 int /*<<< orphan*/  vga_switcheroo_unregister_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int azx_free(struct azx *chip)
{
	int i;

	azx_del_card_list(chip);

	azx_notifier_unregister(chip);

	chip->init_failed = 1; /* to be sure */
	complete_all(&chip->probe_wait);

	if (use_vga_switcheroo(chip)) {
		if (chip->disabled && chip->bus)
			snd_hda_unlock_devices(chip->bus);
		if (chip->vga_switcheroo_registered)
			vga_switcheroo_unregister_client(chip->pci);
	}

	if (chip->initialized) {
		azx_clear_irq_pending(chip);
		for (i = 0; i < chip->num_streams; i++)
			azx_stream_stop(chip, &chip->azx_dev[i]);
		azx_stop_chip(chip);
	}

	if (chip->irq >= 0)
		free_irq(chip->irq, (void*)chip);
	if (chip->msi)
		pci_disable_msi(chip->pci);
	if (chip->remap_addr)
		iounmap(chip->remap_addr);

	if (chip->azx_dev) {
		for (i = 0; i < chip->num_streams; i++)
			if (chip->azx_dev[i].bdl.area) {
				mark_pages_wc(chip, &chip->azx_dev[i].bdl, false);
				snd_dma_free_pages(&chip->azx_dev[i].bdl);
			}
	}
	if (chip->rb.area) {
		mark_pages_wc(chip, &chip->rb, false);
		snd_dma_free_pages(&chip->rb);
	}
	if (chip->posbuf.area) {
		mark_pages_wc(chip, &chip->posbuf, false);
		snd_dma_free_pages(&chip->posbuf);
	}
	if (chip->region_requested)
		pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kfree(chip->azx_dev);
#ifdef CONFIG_SND_HDA_PATCH_LOADER
	if (chip->fw)
		release_firmware(chip->fw);
#endif
	kfree(chip);

	return 0;
}