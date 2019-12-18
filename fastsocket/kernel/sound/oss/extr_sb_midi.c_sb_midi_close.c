#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; scalar_t__ opened; scalar_t__ input_opened; scalar_t__ intr_active; } ;
typedef  TYPE_1__ sb_devc ;
struct TYPE_5__ {TYPE_1__* devc; } ;

/* Variables and functions */
 TYPE_3__** midi_devs ; 
 int /*<<< orphan*/  sb_dsp_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sb_midi_close(int dev)
{
	sb_devc *devc = midi_devs[dev]->devc;
	unsigned long flags;

	if (devc == NULL)
		return;

	spin_lock_irqsave(&devc->lock, flags);
	sb_dsp_reset(devc);
	devc->intr_active = 0;
	devc->input_opened = 0;
	devc->opened = 0;
	spin_unlock_irqrestore(&devc->lock, flags);
}