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
struct gemtek_pci {int mute; int /*<<< orphan*/  current_frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  gemtek_pci_setfrequency (struct gemtek_pci*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gemtek_pci_unmute(struct gemtek_pci *card)
{
	if (card->mute) {
		gemtek_pci_setfrequency(card, card->current_frequency);
		card->mute = false;
	}
}