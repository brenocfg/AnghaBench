#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_2__* dai; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; } ;
struct s6000_i2s_dev {int channel_out; int channel_in; } ;
struct TYPE_4__ {TYPE_1__* cpu_dai; } ;
struct TYPE_3__ {struct s6000_i2s_dev* private_data; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  s6000_i2s_start_channel (struct s6000_i2s_dev*,int) ; 

__attribute__((used)) static void s6000_i2s_start(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct s6000_i2s_dev *dev = rtd->dai->cpu_dai->private_data;
	int channel;

	channel = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) ?
			dev->channel_out : dev->channel_in;

	s6000_i2s_start_channel(dev, channel);
}