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
struct snd_emu10k1_fx8010_irq {unsigned char gpr_running; struct snd_emu10k1_fx8010_irq* next; void* private_data; int /*<<< orphan*/ * handler; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_lock; struct snd_emu10k1_fx8010_irq* irq_handlers; } ;
struct snd_emu10k1 {TYPE_1__ fx8010; int /*<<< orphan*/  dsp_interrupt; } ;
typedef  int /*<<< orphan*/  snd_fx8010_irq_handler_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INTE_FXDSPENABLE ; 
 struct snd_emu10k1_fx8010_irq* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1_fx8010_interrupt ; 
 int /*<<< orphan*/  snd_emu10k1_intr_enable (struct snd_emu10k1*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int snd_emu10k1_fx8010_register_irq_handler(struct snd_emu10k1 *emu,
					    snd_fx8010_irq_handler_t *handler,
					    unsigned char gpr_running,
					    void *private_data,
					    struct snd_emu10k1_fx8010_irq **r_irq)
{
	struct snd_emu10k1_fx8010_irq *irq;
	unsigned long flags;
	
	irq = kmalloc(sizeof(*irq), GFP_ATOMIC);
	if (irq == NULL)
		return -ENOMEM;
	irq->handler = handler;
	irq->gpr_running = gpr_running;
	irq->private_data = private_data;
	irq->next = NULL;
	spin_lock_irqsave(&emu->fx8010.irq_lock, flags);
	if (emu->fx8010.irq_handlers == NULL) {
		emu->fx8010.irq_handlers = irq;
		emu->dsp_interrupt = snd_emu10k1_fx8010_interrupt;
		snd_emu10k1_intr_enable(emu, INTE_FXDSPENABLE);
	} else {
		irq->next = emu->fx8010.irq_handlers;
		emu->fx8010.irq_handlers = irq;
	}
	spin_unlock_irqrestore(&emu->fx8010.irq_lock, flags);
	if (r_irq)
		*r_irq = irq;
	return 0;
}