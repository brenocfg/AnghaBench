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
struct snd_gus_voice {int /*<<< orphan*/  number; int /*<<< orphan*/  client; scalar_t__ midi; int /*<<< orphan*/  use; } ;
struct TYPE_2__ {scalar_t__ pcm_alloc_voices; scalar_t__ pcm_channels; struct snd_gus_voice* voices; } ;
struct snd_gus_card {int /*<<< orphan*/  voice_alloc; TYPE_1__ gf1; } ;

/* Variables and functions */
 int SNDRV_GF1_VOICE_TYPE_PCM ; 
 int /*<<< orphan*/  snd_gf1_alloc_voice_use (struct snd_gus_card*,struct snd_gus_voice*,int,int,int) ; 
 int /*<<< orphan*/  snd_gf1_clear_voices (struct snd_gus_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct snd_gus_voice *snd_gf1_alloc_voice(struct snd_gus_card * gus, int type, int client, int port)
{
	struct snd_gus_voice *pvoice;
	unsigned long flags;
	int idx;

	spin_lock_irqsave(&gus->voice_alloc, flags);
	if (type == SNDRV_GF1_VOICE_TYPE_PCM) {
		if (gus->gf1.pcm_alloc_voices >= gus->gf1.pcm_channels) {
			spin_unlock_irqrestore(&gus->voice_alloc, flags);
			return NULL;
		}
	}
	for (idx = 0; idx < 32; idx++) {
		pvoice = &gus->gf1.voices[idx];
		if (!pvoice->use) {
			snd_gf1_alloc_voice_use(gus, pvoice, type, client, port);
			spin_unlock_irqrestore(&gus->voice_alloc, flags);
			return pvoice;
		}
	} 
	for (idx = 0; idx < 32; idx++) {
		pvoice = &gus->gf1.voices[idx];
		if (pvoice->midi && !pvoice->client) {
			snd_gf1_clear_voices(gus, pvoice->number, pvoice->number);
			snd_gf1_alloc_voice_use(gus, pvoice, type, client, port);
			spin_unlock_irqrestore(&gus->voice_alloc, flags);
			return pvoice;
		}
	} 
	spin_unlock_irqrestore(&gus->voice_alloc, flags);
	return NULL;
}