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
struct snd_emux_voice {int ch; int /*<<< orphan*/  hw; struct snd_emux* emu; scalar_t__ time; int /*<<< orphan*/ * port; int /*<<< orphan*/ * chan; int /*<<< orphan*/  state; } ;
struct snd_emux {int max_voices; int /*<<< orphan*/  voice_lock; int /*<<< orphan*/  hw; struct snd_emux_voice* voices; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_EMUX_ST_OFF ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
snd_emux_init_voices(struct snd_emux *emu)
{
	struct snd_emux_voice *vp;
	int i;
	unsigned long flags;

	spin_lock_irqsave(&emu->voice_lock, flags);
	for (i = 0; i < emu->max_voices; i++) {
		vp = &emu->voices[i];
		vp->ch = -1; /* not used */
		vp->state = SNDRV_EMUX_ST_OFF;
		vp->chan = NULL;
		vp->port = NULL;
		vp->time = 0;
		vp->emu = emu;
		vp->hw = emu->hw;
	}
	spin_unlock_irqrestore(&emu->voice_lock, flags);
}