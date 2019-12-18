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
struct sdhci_pci_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int ricoh_mmc_resume(struct sdhci_pci_chip *chip)
{
	/* Apply a delay to allow controller to settle */
	/* Otherwise it becomes confused if card state changed
		during suspend */
	msleep(500);
	return 0;
}