#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ irq; int /*<<< orphan*/  pci; int /*<<< orphan*/  core; } ;
typedef  TYPE_1__ snd_cx88_card_t ;

/* Variables and functions */
 int /*<<< orphan*/  cx88_core_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_cx88_free(snd_cx88_card_t *chip)
{

	if (chip->irq >= 0)
		free_irq(chip->irq, chip);

	cx88_core_put(chip->core,chip->pci);

	pci_disable_device(chip->pci);
	return 0;
}