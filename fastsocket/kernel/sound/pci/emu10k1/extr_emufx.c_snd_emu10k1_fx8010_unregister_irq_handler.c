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
struct snd_emu10k1_fx8010_irq {struct snd_emu10k1_fx8010_irq* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_lock; struct snd_emu10k1_fx8010_irq* irq_handlers; } ;
struct snd_emu10k1 {TYPE_1__ fx8010; int /*<<< orphan*/ * dsp_interrupt; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTE_FXDSPENABLE ; 
 int /*<<< orphan*/  kfree (struct snd_emu10k1_fx8010_irq*) ; 
 int /*<<< orphan*/  snd_emu10k1_intr_disable (struct snd_emu10k1*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int snd_emu10k1_fx8010_unregister_irq_handler(struct snd_emu10k1 *emu,
					      struct snd_emu10k1_fx8010_irq *irq)
{
	struct snd_emu10k1_fx8010_irq *tmp;
	unsigned long flags;
	
	spin_lock_irqsave(&emu->fx8010.irq_lock, flags);
	if ((tmp = emu->fx8010.irq_handlers) == irq) {
		emu->fx8010.irq_handlers = tmp->next;
		if (emu->fx8010.irq_handlers == NULL) {
			snd_emu10k1_intr_disable(emu, INTE_FXDSPENABLE);
			emu->dsp_interrupt = NULL;
		}
	} else {
		while (tmp && tmp->next != irq)
			tmp = tmp->next;
		if (tmp)
			tmp->next = tmp->next->next;
	}
	spin_unlock_irqrestore(&emu->fx8010.irq_lock, flags);
	kfree(irq);
	return 0;
}