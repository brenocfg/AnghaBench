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
struct gelic_card {int /*<<< orphan*/  irq_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  GELIC_CARD_RXINT ; 
 int /*<<< orphan*/  gelic_card_set_irq_mask (struct gelic_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void gelic_card_rx_irq_on(struct gelic_card *card)
{
	card->irq_mask |= GELIC_CARD_RXINT;
	gelic_card_set_irq_mask(card, card->irq_mask);
}