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
struct snd_emux_voice {int ch; int /*<<< orphan*/  state; TYPE_1__* emu; } ;
struct snd_emux {int /*<<< orphan*/  voice_lock; struct snd_emux_voice* voices; } ;
struct snd_emu10k1 {struct snd_emux* synth; } ;
struct best_voice {size_t voice; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_voices; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SNDRV_EMUX_ST_OFF ; 
 int V_END ; 
 int /*<<< orphan*/  lookup_voices (struct snd_emux*,struct snd_emu10k1*,struct best_voice*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
snd_emu10k1_synth_get_voice(struct snd_emu10k1 *hw)
{
	struct snd_emux *emu;
	struct snd_emux_voice *vp;
	struct best_voice best[V_END];
	unsigned long flags;
	int i;

	emu = hw->synth;

	spin_lock_irqsave(&emu->voice_lock, flags);
	lookup_voices(emu, hw, best, 1); /* no OFF voices */
	for (i = 0; i < V_END; i++) {
		if (best[i].voice >= 0) {
			int ch;
			vp = &emu->voices[best[i].voice];
			if ((ch = vp->ch) < 0) {
				/*
				printk(KERN_WARNING
				       "synth_get_voice: ch < 0 (%d) ??", i);
				*/
				continue;
			}
			vp->emu->num_voices--;
			vp->ch = -1;
			vp->state = SNDRV_EMUX_ST_OFF;
			spin_unlock_irqrestore(&emu->voice_lock, flags);
			return ch;
		}
	}
	spin_unlock_irqrestore(&emu->voice_lock, flags);

	/* not found */
	return -ENOMEM;
}