#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct snd_emu10k1_pcm {scalar_t__ type; TYPE_2__* extra; TYPE_2__** voices; TYPE_1__* emu; } ;
struct TYPE_7__ {int number; int /*<<< orphan*/  interrupt; struct snd_emu10k1_pcm* epcm; } ;
struct TYPE_6__ {TYPE_2__* voices; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__**) ; 
 int /*<<< orphan*/  EMU10K1_EFX ; 
 int /*<<< orphan*/  EMU10K1_PCM ; 
 scalar_t__ PLAYBACK_EMUVOICE ; 
 int /*<<< orphan*/  snd_emu10k1_pcm_interrupt ; 
 int snd_emu10k1_voice_alloc (TYPE_1__*,int /*<<< orphan*/ ,int,TYPE_2__**) ; 
 int /*<<< orphan*/  snd_emu10k1_voice_free (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int snd_emu10k1_pcm_channel_alloc(struct snd_emu10k1_pcm * epcm, int voices)
{
	int err, i;

	if (epcm->voices[1] != NULL && voices < 2) {
		snd_emu10k1_voice_free(epcm->emu, epcm->voices[1]);
		epcm->voices[1] = NULL;
	}
	for (i = 0; i < voices; i++) {
		if (epcm->voices[i] == NULL)
			break;
	}
	if (i == voices)
		return 0; /* already allocated */

	for (i = 0; i < ARRAY_SIZE(epcm->voices); i++) {
		if (epcm->voices[i]) {
			snd_emu10k1_voice_free(epcm->emu, epcm->voices[i]);
			epcm->voices[i] = NULL;
		}
	}
	err = snd_emu10k1_voice_alloc(epcm->emu,
				      epcm->type == PLAYBACK_EMUVOICE ? EMU10K1_PCM : EMU10K1_EFX,
				      voices,
				      &epcm->voices[0]);
	
	if (err < 0)
		return err;
	epcm->voices[0]->epcm = epcm;
	if (voices > 1) {
		for (i = 1; i < voices; i++) {
			epcm->voices[i] = &epcm->emu->voices[epcm->voices[0]->number + i];
			epcm->voices[i]->epcm = epcm;
		}
	}
	if (epcm->extra == NULL) {
		err = snd_emu10k1_voice_alloc(epcm->emu,
					      epcm->type == PLAYBACK_EMUVOICE ? EMU10K1_PCM : EMU10K1_EFX,
					      1,
					      &epcm->extra);
		if (err < 0) {
			/*
			printk(KERN_DEBUG "pcm_channel_alloc: "
			       "failed extra: voices=%d, frame=%d\n",
			       voices, frame);
			*/
			for (i = 0; i < voices; i++) {
				snd_emu10k1_voice_free(epcm->emu, epcm->voices[i]);
				epcm->voices[i] = NULL;
			}
			return err;
		}
		epcm->extra->epcm = epcm;
		epcm->extra->interrupt = snd_emu10k1_pcm_interrupt;
	}
	return 0;
}