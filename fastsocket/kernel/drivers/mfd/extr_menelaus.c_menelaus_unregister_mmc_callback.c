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
struct TYPE_2__ {scalar_t__ mmc_callback_data; int /*<<< orphan*/ * mmc_callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  MENELAUS_MMC_S1CD_IRQ ; 
 int /*<<< orphan*/  MENELAUS_MMC_S1D1_IRQ ; 
 int /*<<< orphan*/  MENELAUS_MMC_S2CD_IRQ ; 
 int /*<<< orphan*/  MENELAUS_MMC_S2D1_IRQ ; 
 int /*<<< orphan*/  menelaus_remove_irq_work (int /*<<< orphan*/ ) ; 
 TYPE_1__* the_menelaus ; 

void menelaus_unregister_mmc_callback(void)
{
	menelaus_remove_irq_work(MENELAUS_MMC_S1CD_IRQ);
	menelaus_remove_irq_work(MENELAUS_MMC_S2CD_IRQ);
	menelaus_remove_irq_work(MENELAUS_MMC_S1D1_IRQ);
	menelaus_remove_irq_work(MENELAUS_MMC_S2D1_IRQ);

	the_menelaus->mmc_callback = NULL;
	the_menelaus->mmc_callback_data = 0;
}