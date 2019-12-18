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
struct snd_opl4 {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  on_voices; } ;
struct snd_midi_channel {int midi_program; scalar_t__ drum_channel; } ;
struct opl4_voice {int note; int velocity; int reg_f_number; int reg_misc; scalar_t__ number; struct opl4_sound const* sound; int /*<<< orphan*/  reg_lfo_vibrato; int /*<<< orphan*/  level_direct; struct snd_midi_channel* chan; int /*<<< orphan*/  list; } ;
struct opl4_sound {int tone; int /*<<< orphan*/  reg_lfo_vibrato; } ;
struct opl4_region_ptr {int count; TYPE_1__* regions; } ;
struct TYPE_2__ {int key_min; int key_max; struct opl4_sound sound; } ;

/* Variables and functions */
 int OPL4_KEY_ON_BIT ; 
 int /*<<< orphan*/  OPL4_LEVEL_DIRECT_BIT ; 
 int OPL4_LFO_RESET_BIT ; 
 scalar_t__ OPL4_REG_F_NUMBER ; 
 scalar_t__ OPL4_REG_MISC ; 
 scalar_t__ OPL4_REG_TONE_NUMBER ; 
 int OPL4_TONE_NUMBER_BIT8 ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct opl4_voice* snd_opl4_get_voice (struct snd_opl4*) ; 
 int /*<<< orphan*/  snd_opl4_update_pan (struct snd_opl4*,struct opl4_voice*) ; 
 int /*<<< orphan*/  snd_opl4_update_pitch (struct snd_opl4*,struct opl4_voice*) ; 
 int /*<<< orphan*/  snd_opl4_update_tone_parameters (struct snd_opl4*,struct opl4_voice*) ; 
 int /*<<< orphan*/  snd_opl4_update_vibrato_depth (struct snd_opl4*,struct opl4_voice*) ; 
 int /*<<< orphan*/  snd_opl4_update_volume (struct snd_opl4*,struct opl4_voice*) ; 
 int /*<<< orphan*/  snd_opl4_wait_for_wave_headers (struct snd_opl4*) ; 
 int /*<<< orphan*/  snd_opl4_write (struct snd_opl4*,scalar_t__,int) ; 
 struct opl4_region_ptr* snd_yrw801_regions ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void snd_opl4_note_on(void *private_data, int note, int vel, struct snd_midi_channel *chan)
{
	struct snd_opl4 *opl4 = private_data;
	const struct opl4_region_ptr *regions;
	struct opl4_voice *voice[2];
	const struct opl4_sound *sound[2];
	int voices = 0, i;
	unsigned long flags;

	/* determine the number of voices and voice parameters */
	i = chan->drum_channel ? 0x80 : (chan->midi_program & 0x7f);
	regions = &snd_yrw801_regions[i];
	for (i = 0; i < regions->count; i++) {
		if (note >= regions->regions[i].key_min &&
		    note <= regions->regions[i].key_max) {
			sound[voices] = &regions->regions[i].sound;
			if (++voices >= 2)
				break;
		}
	}

	/* allocate and initialize the needed voices */
	spin_lock_irqsave(&opl4->reg_lock, flags);
	for (i = 0; i < voices; i++) {
		voice[i] = snd_opl4_get_voice(opl4);
		list_del(&voice[i]->list);
		list_add_tail(&voice[i]->list, &opl4->on_voices);
		voice[i]->chan = chan;
		voice[i]->note = note;
		voice[i]->velocity = vel & 0x7f;
		voice[i]->sound = sound[i];
	}

	/* set tone number (triggers header loading) */
	for (i = 0; i < voices; i++) {
		voice[i]->reg_f_number =
			(sound[i]->tone >> 8) & OPL4_TONE_NUMBER_BIT8;
		snd_opl4_write(opl4, OPL4_REG_F_NUMBER + voice[i]->number,
			       voice[i]->reg_f_number);
		snd_opl4_write(opl4, OPL4_REG_TONE_NUMBER + voice[i]->number,
			       sound[i]->tone & 0xff);
	}

	/* set parameters which can be set while loading */
	for (i = 0; i < voices; i++) {
		voice[i]->reg_misc = OPL4_LFO_RESET_BIT;
		snd_opl4_update_pan(opl4, voice[i]);
		snd_opl4_update_pitch(opl4, voice[i]);
		voice[i]->level_direct = OPL4_LEVEL_DIRECT_BIT;
		snd_opl4_update_volume(opl4, voice[i]);
	}
	spin_unlock_irqrestore(&opl4->reg_lock, flags);

	/* wait for completion of loading */
	snd_opl4_wait_for_wave_headers(opl4);

	/* set remaining parameters */
	spin_lock_irqsave(&opl4->reg_lock, flags);
	for (i = 0; i < voices; i++) {
		snd_opl4_update_tone_parameters(opl4, voice[i]);
		voice[i]->reg_lfo_vibrato = voice[i]->sound->reg_lfo_vibrato;
		snd_opl4_update_vibrato_depth(opl4, voice[i]);
	}

	/* finally, switch on all voices */
	for (i = 0; i < voices; i++) {
		voice[i]->reg_misc =
			(voice[i]->reg_misc & 0x1f) | OPL4_KEY_ON_BIT;
		snd_opl4_write(opl4, OPL4_REG_MISC + voice[i]->number,
			       voice[i]->reg_misc);
	}
	spin_unlock_irqrestore(&opl4->reg_lock, flags);
}