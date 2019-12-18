#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  my_mididev; int /*<<< orphan*/  (* midi_input_intr ) (int /*<<< orphan*/ ,unsigned char) ;scalar_t__ input_opened; } ;
typedef  TYPE_1__ sb_devc ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_READ ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned char) ; 

void sb_midi_interrupt(sb_devc * devc)
{
	unsigned long   flags;
	unsigned char   data;

	if (devc == NULL)
		return;

	spin_lock_irqsave(&devc->lock, flags);

	data = inb(DSP_READ);
	if (devc->input_opened)
		devc->midi_input_intr(devc->my_mididev, data);

	spin_unlock_irqrestore(&devc->lock, flags);
}