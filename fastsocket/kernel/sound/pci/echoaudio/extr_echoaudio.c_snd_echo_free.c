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
struct echoaudio {scalar_t__ irq; int /*<<< orphan*/  pci; scalar_t__ iores; scalar_t__ dsp_registers; int /*<<< orphan*/  commpage_dma_buf; scalar_t__ comm_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_INIT (char*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct echoaudio*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct echoaudio*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_and_free_resource (scalar_t__) ; 
 int /*<<< orphan*/  rest_in_peace (struct echoaudio*) ; 
 int /*<<< orphan*/  snd_dma_free_pages (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_echo_free(struct echoaudio *chip)
{
	DE_INIT(("Stop DSP...\n"));
	if (chip->comm_page)
		rest_in_peace(chip);
	DE_INIT(("Stopped.\n"));

	if (chip->irq >= 0)
		free_irq(chip->irq, chip);

	if (chip->comm_page)
		snd_dma_free_pages(&chip->commpage_dma_buf);

	if (chip->dsp_registers)
		iounmap(chip->dsp_registers);

	if (chip->iores)
		release_and_free_resource(chip->iores);

	DE_INIT(("MMIO freed.\n"));

	pci_disable_device(chip->pci);

	/* release chip data */
	kfree(chip);
	DE_INIT(("Chip freed.\n"));
	return 0;
}