#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct aaci_runtime {int pcm_open; TYPE_2__* pcm; } ;
struct TYPE_5__ {TYPE_1__* r; } ;
struct TYPE_4__ {int /*<<< orphan*/  slots; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  aaci_pcm_hw_free (struct snd_pcm_substream*) ; 
 int devdma_hw_alloc (int /*<<< orphan*/ *,struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_ac97_pcm_close (TYPE_2__*) ; 
 int snd_ac97_pcm_open (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aaci_pcm_hw_params(struct snd_pcm_substream *substream,
			      struct aaci_runtime *aacirun,
			      struct snd_pcm_hw_params *params)
{
	int err;

	aaci_pcm_hw_free(substream);
	if (aacirun->pcm_open) {
		snd_ac97_pcm_close(aacirun->pcm);
		aacirun->pcm_open = 0;
	}

	err = devdma_hw_alloc(NULL, substream,
			      params_buffer_bytes(params));
	if (err < 0)
		goto out;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		err = snd_ac97_pcm_open(aacirun->pcm, params_rate(params),
					params_channels(params),
					aacirun->pcm->r[0].slots);
	else
		err = snd_ac97_pcm_open(aacirun->pcm, params_rate(params),
					params_channels(params),
					aacirun->pcm->r[0].slots);

	if (err)
		goto out;

	aacirun->pcm_open = 1;

 out:
	return err;
}