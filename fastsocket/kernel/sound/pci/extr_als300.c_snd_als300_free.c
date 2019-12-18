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
struct snd_als300 {scalar_t__ irq; int /*<<< orphan*/  pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_DISABLE ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_als300*) ; 
 int /*<<< orphan*/  kfree (struct snd_als300*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_als300_dbgcallenter () ; 
 int /*<<< orphan*/  snd_als300_dbgcallleave () ; 
 int /*<<< orphan*/  snd_als300_set_irq_flag (struct snd_als300*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_als300_free(struct snd_als300 *chip)
{
	snd_als300_dbgcallenter();
	snd_als300_set_irq_flag(chip, IRQ_DISABLE);
	if (chip->irq >= 0)
		free_irq(chip->irq, chip);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kfree(chip);
	snd_als300_dbgcallleave();
	return 0;
}