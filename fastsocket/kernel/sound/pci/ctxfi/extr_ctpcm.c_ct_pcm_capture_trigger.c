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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct ct_atc_pcm* private_data; } ;
struct ct_atc_pcm {int dummy; } ;
struct ct_atc {int /*<<< orphan*/  (* pcm_capture_stop ) (struct ct_atc*,struct ct_atc_pcm*) ;int /*<<< orphan*/  (* pcm_capture_start ) (struct ct_atc*,struct ct_atc_pcm*) ;} ;

/* Variables and functions */
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 struct ct_atc* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  stub1 (struct ct_atc*,struct ct_atc_pcm*) ; 
 int /*<<< orphan*/  stub2 (struct ct_atc*,struct ct_atc_pcm*) ; 
 int /*<<< orphan*/  stub3 (struct ct_atc*,struct ct_atc_pcm*) ; 

__attribute__((used)) static int
ct_pcm_capture_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct ct_atc *atc = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct ct_atc_pcm *apcm = runtime->private_data;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		atc->pcm_capture_start(atc, apcm);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		atc->pcm_capture_stop(atc, apcm);
		break;
	default:
		atc->pcm_capture_stop(atc, apcm);
		break;
	}

	return 0;
}