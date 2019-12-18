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
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  davinci_mcbsp_start (struct davinci_mcbsp_dev*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  davinci_mcbsp_stop (struct davinci_mcbsp_dev*,int) ; 

__attribute__((used)) static int davinci_i2s_prepare(struct snd_pcm_substream *substream,
		struct snd_soc_dai *dai)
{
	struct davinci_mcbsp_dev *dev = dai->private_data;
	int playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	davinci_mcbsp_stop(dev, playback);
	if ((dev->pcr & DAVINCI_MCBSP_PCR_FSXM) == 0) {
		/* codec is master */
		davinci_mcbsp_start(dev, substream);
	}
	return 0;
}