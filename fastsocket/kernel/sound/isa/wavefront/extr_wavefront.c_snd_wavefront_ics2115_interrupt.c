#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ interrupts_are_midi; } ;
struct TYPE_6__ {TYPE_1__ wavefront; } ;
typedef  TYPE_2__ snd_wavefront_card_t ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  snd_wavefront_internal_interrupt (TYPE_2__*) ; 
 int /*<<< orphan*/  snd_wavefront_midi_interrupt (TYPE_2__*) ; 

__attribute__((used)) static irqreturn_t snd_wavefront_ics2115_interrupt(int irq, void *dev_id)
{
	snd_wavefront_card_t *acard;

	acard = (snd_wavefront_card_t *) dev_id;

	if (acard == NULL) 
		return IRQ_NONE;

	if (acard->wavefront.interrupts_are_midi) {
		snd_wavefront_midi_interrupt (acard);
	} else {
		snd_wavefront_internal_interrupt (acard);
	}
	return IRQ_HANDLED;
}