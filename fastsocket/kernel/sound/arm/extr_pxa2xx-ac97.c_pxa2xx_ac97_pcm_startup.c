#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {scalar_t__ stream; TYPE_3__* pcm; struct snd_pcm_runtime* runtime; } ;
struct TYPE_10__ {int channels_min; int channels_max; int /*<<< orphan*/  rates; } ;
struct snd_pcm_runtime {TYPE_4__ hw; } ;
struct TYPE_11__ {int (* startup ) (struct snd_pcm_substream*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  priv; } ;
typedef  TYPE_5__ pxa2xx_audio_ops_t ;
struct TYPE_12__ {int /*<<< orphan*/ * rates; } ;
struct TYPE_9__ {TYPE_2__* card; } ;
struct TYPE_8__ {TYPE_1__* dev; } ;
struct TYPE_7__ {TYPE_5__* platform_data; } ;

/* Variables and functions */
 int AC97_RATES_ADC ; 
 int AC97_RATES_FRONT_DAC ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 TYPE_6__* pxa2xx_ac97_ac97 ; 
 int /*<<< orphan*/  snd_pcm_limit_hw_rates (struct snd_pcm_runtime*) ; 
 int stub1 (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pxa2xx_ac97_pcm_startup(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	pxa2xx_audio_ops_t *platform_ops;
	int r;

	runtime->hw.channels_min = 2;
	runtime->hw.channels_max = 2;

	r = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) ?
	    AC97_RATES_FRONT_DAC : AC97_RATES_ADC;
	runtime->hw.rates = pxa2xx_ac97_ac97->rates[r];
	snd_pcm_limit_hw_rates(runtime);

       	platform_ops = substream->pcm->card->dev->platform_data;
	if (platform_ops && platform_ops->startup)
		return platform_ops->startup(substream, platform_ops->priv);
	else
		return 0;
}