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
struct fst_card_info {scalar_t__ family; scalar_t__ pci_conf; int /*<<< orphan*/  ctlmem; } ;

/* Variables and functions */
 scalar_t__ FST_FAMILY_TXU ; 
 scalar_t__ INTCSR_9052 ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  readb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
fst_clear_intr(struct fst_card_info *card)
{
	if (card->family == FST_FAMILY_TXU) {
		(void) readb(card->ctlmem);
	} else {
		/* Poke the appropriate PLX chip register (same as enabling interrupts)
		 */
		outw(0x0543, card->pci_conf + INTCSR_9052);
	}
}