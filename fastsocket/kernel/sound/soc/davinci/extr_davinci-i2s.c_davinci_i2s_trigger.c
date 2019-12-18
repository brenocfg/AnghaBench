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
struct snd_soc_dai {struct davinci_mcbsp_dev* private_data; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct davinci_mcbsp_dev {int pcr; } ;

/* Variables and functions */
 int DAVINCI_MCBSP_PCR_FSXM ; 
 int EINVAL ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  davinci_mcbsp_start (struct davinci_mcbsp_dev*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  davinci_mcbsp_stop (struct davinci_mcbsp_dev*,int) ; 

__attribute__((used)) static int davinci_i2s_trigger(struct snd_pcm_substream *substream, int cmd,
			       struct snd_soc_dai *dai)
{
	struct davinci_mcbsp_dev *dev = dai->private_data;
	int ret = 0;
	int playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	if ((dev->pcr & DAVINCI_MCBSP_PCR_FSXM) == 0)
		return 0;	/* return if codec is master */

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		davinci_mcbsp_start(dev, substream);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		davinci_mcbsp_stop(dev, playback);
		break;
	default:
		ret = -EINVAL;
	}
	return ret;
}