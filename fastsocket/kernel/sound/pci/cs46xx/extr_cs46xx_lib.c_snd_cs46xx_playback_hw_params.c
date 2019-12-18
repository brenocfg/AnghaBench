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
struct snd_pcm_substream {int /*<<< orphan*/ * ops; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ dma_bytes; scalar_t__ dma_addr; int /*<<< orphan*/ * dma_area; struct snd_cs46xx_pcm* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * area; scalar_t__ bytes; scalar_t__ addr; } ;
struct snd_cs46xx_pcm {scalar_t__ pcm_channel_id; TYPE_1__ hw_buf; int /*<<< orphan*/  pcm_channel; } ;
struct snd_cs46xx {int /*<<< orphan*/  spos_mutex; } ;

/* Variables and functions */
 scalar_t__ CS46XX_FRAGS ; 
 scalar_t__ DSP_IEC958_CHANNEL ; 
 scalar_t__ DSP_PCM_CENTER_LFE_CHANNEL ; 
 scalar_t__ DSP_PCM_MAIN_CHANNEL ; 
 scalar_t__ DSP_PCM_REAR_CHANNEL ; 
 int EINVAL ; 
 int ENXIO ; 
 scalar_t__ _cs46xx_adjust_sample_rate (struct snd_cs46xx*,struct snd_cs46xx_pcm*,int) ; 
 scalar_t__ cs46xx_dsp_pcm_channel_set_period (struct snd_cs46xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int params_period_bytes (struct snd_pcm_hw_params*) ; 
 scalar_t__ params_periods (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_BUG () ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_cs46xx_playback_clfe_ops ; 
 int /*<<< orphan*/  snd_cs46xx_playback_iec958_ops ; 
 int /*<<< orphan*/  snd_cs46xx_playback_indirect_clfe_ops ; 
 int /*<<< orphan*/  snd_cs46xx_playback_indirect_iec958_ops ; 
 int /*<<< orphan*/  snd_cs46xx_playback_indirect_ops ; 
 int /*<<< orphan*/  snd_cs46xx_playback_indirect_rear_ops ; 
 int /*<<< orphan*/  snd_cs46xx_playback_ops ; 
 int /*<<< orphan*/  snd_cs46xx_playback_rear_ops ; 
 int /*<<< orphan*/  snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct snd_cs46xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_printdd (char*,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_cs46xx_playback_hw_params(struct snd_pcm_substream *substream,
					 struct snd_pcm_hw_params *hw_params)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_cs46xx_pcm *cpcm;
	int err;
#ifdef CONFIG_SND_CS46XX_NEW_DSP
	struct snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	int sample_rate = params_rate(hw_params);
	int period_size = params_period_bytes(hw_params);
#endif
	cpcm = runtime->private_data;

#ifdef CONFIG_SND_CS46XX_NEW_DSP
	if (snd_BUG_ON(!sample_rate))
		return -ENXIO;

	mutex_lock(&chip->spos_mutex);

	if (_cs46xx_adjust_sample_rate (chip,cpcm,sample_rate)) {
		mutex_unlock(&chip->spos_mutex);
		return -ENXIO;
	}

	snd_BUG_ON(!cpcm->pcm_channel);
	if (!cpcm->pcm_channel) {
		mutex_unlock(&chip->spos_mutex);
		return -ENXIO;
	}


	if (cs46xx_dsp_pcm_channel_set_period (chip,cpcm->pcm_channel,period_size)) {
		 mutex_unlock(&chip->spos_mutex);
		 return -EINVAL;
	 }

	snd_printdd ("period_size (%d), periods (%d) buffer_size(%d)\n",
		     period_size, params_periods(hw_params),
		     params_buffer_bytes(hw_params));
#endif

	if (params_periods(hw_params) == CS46XX_FRAGS) {
		if (runtime->dma_area != cpcm->hw_buf.area)
			snd_pcm_lib_free_pages(substream);
		runtime->dma_area = cpcm->hw_buf.area;
		runtime->dma_addr = cpcm->hw_buf.addr;
		runtime->dma_bytes = cpcm->hw_buf.bytes;


#ifdef CONFIG_SND_CS46XX_NEW_DSP
		if (cpcm->pcm_channel_id == DSP_PCM_MAIN_CHANNEL) {
			substream->ops = &snd_cs46xx_playback_ops;
		} else if (cpcm->pcm_channel_id == DSP_PCM_REAR_CHANNEL) {
			substream->ops = &snd_cs46xx_playback_rear_ops;
		} else if (cpcm->pcm_channel_id == DSP_PCM_CENTER_LFE_CHANNEL) {
			substream->ops = &snd_cs46xx_playback_clfe_ops;
		} else if (cpcm->pcm_channel_id == DSP_IEC958_CHANNEL) {
			substream->ops = &snd_cs46xx_playback_iec958_ops;
		} else {
			snd_BUG();
		}
#else
		substream->ops = &snd_cs46xx_playback_ops;
#endif

	} else {
		if (runtime->dma_area == cpcm->hw_buf.area) {
			runtime->dma_area = NULL;
			runtime->dma_addr = 0;
			runtime->dma_bytes = 0;
		}
		if ((err = snd_pcm_lib_malloc_pages(substream, params_buffer_bytes(hw_params))) < 0) {
#ifdef CONFIG_SND_CS46XX_NEW_DSP
			mutex_unlock(&chip->spos_mutex);
#endif
			return err;
		}

#ifdef CONFIG_SND_CS46XX_NEW_DSP
		if (cpcm->pcm_channel_id == DSP_PCM_MAIN_CHANNEL) {
			substream->ops = &snd_cs46xx_playback_indirect_ops;
		} else if (cpcm->pcm_channel_id == DSP_PCM_REAR_CHANNEL) {
			substream->ops = &snd_cs46xx_playback_indirect_rear_ops;
		} else if (cpcm->pcm_channel_id == DSP_PCM_CENTER_LFE_CHANNEL) {
			substream->ops = &snd_cs46xx_playback_indirect_clfe_ops;
		} else if (cpcm->pcm_channel_id == DSP_IEC958_CHANNEL) {
			substream->ops = &snd_cs46xx_playback_indirect_iec958_ops;
		} else {
			snd_BUG();
		}
#else
		substream->ops = &snd_cs46xx_playback_indirect_ops;
#endif

	}

#ifdef CONFIG_SND_CS46XX_NEW_DSP
	mutex_unlock(&chip->spos_mutex);
#endif

	return 0;
}