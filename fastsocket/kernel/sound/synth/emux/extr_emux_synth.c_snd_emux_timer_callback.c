#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_emux_voice {scalar_t__ state; scalar_t__ ontime; } ;
struct TYPE_4__ {scalar_t__ expires; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* release ) (struct snd_emux_voice*) ;} ;
struct snd_emux {int max_voices; int timer_active; int /*<<< orphan*/  voice_lock; TYPE_2__ tlist; TYPE_1__ ops; struct snd_emux_voice* voices; } ;

/* Variables and functions */
 scalar_t__ SNDRV_EMUX_ST_PENDING ; 
 scalar_t__ SNDRV_EMUX_ST_RELEASED ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct snd_emux_voice*) ; 

void snd_emux_timer_callback(unsigned long data)
{
	struct snd_emux *emu = (struct snd_emux *) data;
	struct snd_emux_voice *vp;
	unsigned long flags;
	int ch, do_again = 0;

	spin_lock_irqsave(&emu->voice_lock, flags);
	for (ch = 0; ch < emu->max_voices; ch++) {
		vp = &emu->voices[ch];
		if (vp->state == SNDRV_EMUX_ST_PENDING) {
			if (vp->ontime == jiffies)
				do_again++; /* release this at the next interrupt */
			else {
				emu->ops.release(vp);
				vp->state = SNDRV_EMUX_ST_RELEASED;
			}
		}
	}
	if (do_again) {
		emu->tlist.expires = jiffies + 1;
		add_timer(&emu->tlist);
		emu->timer_active = 1;
	} else
		emu->timer_active = 0;
	spin_unlock_irqrestore(&emu->voice_lock, flags);
}