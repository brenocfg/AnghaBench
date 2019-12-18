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
struct mmci_card_event {int /*<<< orphan*/  workq; } ;

/* Variables and functions */
 int /*<<< orphan*/  U300_GPIO_PIN_MMC_CD ; 
 int /*<<< orphan*/  disable_irq_on_gpio_pin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mmci_callback(void *data)
{
	struct mmci_card_event *mmci_card = data;

	disable_irq_on_gpio_pin(U300_GPIO_PIN_MMC_CD);
	schedule_work(&mmci_card->workq);

	return 0;
}