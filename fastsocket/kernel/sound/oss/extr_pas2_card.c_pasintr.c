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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  pas_midi_interrupt () ; 
 int /*<<< orphan*/  pas_pcm_interrupt (int,int) ; 
 int pas_read (int) ; 
 int /*<<< orphan*/  pas_write (int,int) ; 

__attribute__((used)) static irqreturn_t pasintr(int irq, void *dev_id)
{
	int             status;

	status = pas_read(0x0B89);
	pas_write(status, 0x0B89);	/* Clear interrupt */

	if (status & 0x08)
	{
		  pas_pcm_interrupt(status, 1);
		  status &= ~0x08;
	}
	if (status & 0x10)
	{
		  pas_midi_interrupt();
		  status &= ~0x10;
	}
	return IRQ_HANDLED;
}