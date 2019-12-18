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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
#define  SNDRV_PCM_HW_PARAM_ACCESS 135 
#define  SNDRV_PCM_HW_PARAM_BUFFER_SIZE 134 
#define  SNDRV_PCM_HW_PARAM_CHANNELS 133 
#define  SNDRV_PCM_HW_PARAM_FORMAT 132 
#define  SNDRV_PCM_HW_PARAM_PERIOD_TIME 131 
#define  SNDRV_PCM_HW_PARAM_RATE 130 
#define  SNDRV_PCM_HW_PARAM_SUBFORMAT 129 
#define  SNDRV_PCM_HW_PARAM_TICK_TIME 128 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_pcm_hw_param_first (struct snd_pcm_substream*,struct snd_pcm_hw_params*,int,int /*<<< orphan*/ *) ; 
 int snd_pcm_hw_param_last (struct snd_pcm_substream*,struct snd_pcm_hw_params*,int,int /*<<< orphan*/ *) ; 

int snd_pcm_hw_params_choose(struct snd_pcm_substream *pcm,
			     struct snd_pcm_hw_params *params)
{
	static int vars[] = {
		SNDRV_PCM_HW_PARAM_ACCESS,
		SNDRV_PCM_HW_PARAM_FORMAT,
		SNDRV_PCM_HW_PARAM_SUBFORMAT,
		SNDRV_PCM_HW_PARAM_CHANNELS,
		SNDRV_PCM_HW_PARAM_RATE,
		SNDRV_PCM_HW_PARAM_PERIOD_TIME,
		SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
		SNDRV_PCM_HW_PARAM_TICK_TIME,
		-1
	};
	int err, *v;

	for (v = vars; *v != -1; v++) {
		if (*v != SNDRV_PCM_HW_PARAM_BUFFER_SIZE)
			err = snd_pcm_hw_param_first(pcm, params, *v, NULL);
		else
			err = snd_pcm_hw_param_last(pcm, params, *v, NULL);
		if (snd_BUG_ON(err < 0))
			return err;
	}
	return 0;
}