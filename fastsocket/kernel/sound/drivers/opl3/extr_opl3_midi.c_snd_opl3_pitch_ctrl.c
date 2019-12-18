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
struct snd_opl3_voice {scalar_t__ state; struct snd_midi_channel* chan; } ;
struct snd_opl3 {scalar_t__ synth_mode; int max_voices; int /*<<< orphan*/  voice_lock; struct snd_opl3_voice* voices; } ;
struct snd_midi_channel {size_t number; } ;

/* Variables and functions */
 size_t MAX_OPL3_VOICES ; 
 scalar_t__ SNDRV_OPL3_MODE_SEQ ; 
 int* snd_opl3_oss_map ; 
 int /*<<< orphan*/  snd_opl3_update_pitch (struct snd_opl3*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_opl3_pitch_ctrl(struct snd_opl3 *opl3, struct snd_midi_channel *chan)
{
	int voice;
	struct snd_opl3_voice *vp;

	unsigned long flags;

	spin_lock_irqsave(&opl3->voice_lock, flags);

	if (opl3->synth_mode == SNDRV_OPL3_MODE_SEQ) {
		for (voice = 0; voice < opl3->max_voices; voice++) {
			vp = &opl3->voices[voice];
			if (vp->state > 0 && vp->chan == chan) {
				snd_opl3_update_pitch(opl3, voice);
			}
		}
	} else {
		/* remap OSS voices */
		if (chan->number < MAX_OPL3_VOICES) {
			voice = snd_opl3_oss_map[chan->number];		
			snd_opl3_update_pitch(opl3, voice);
		}
	}
	spin_unlock_irqrestore(&opl3->voice_lock, flags);
}