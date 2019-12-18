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
struct twl4030_priv {struct snd_pcm_substream* master_substream; scalar_t__ configured; struct snd_pcm_substream* slave_substream; } ;
struct snd_soc_pcm_runtime {struct snd_soc_device* socdev; } ;
struct snd_soc_device {TYPE_1__* card; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_soc_codec {struct twl4030_priv* private_data; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_2__ {struct snd_soc_codec* codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int TWL4030_OPTION_1 ; 
 int /*<<< orphan*/  TWL4030_REG_CODEC_MODE ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_minmax (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  twl4030_constraints (struct twl4030_priv*,struct snd_pcm_substream*) ; 
 int twl4030_read_reg_cache (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_startup(struct snd_pcm_substream *substream,
			   struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_device *socdev = rtd->socdev;
	struct snd_soc_codec *codec = socdev->card->codec;
	struct twl4030_priv *twl4030 = codec->private_data;

	if (twl4030->master_substream) {
		twl4030->slave_substream = substream;
		/* The DAI has one configuration for playback and capture, so
		 * if the DAI has been already configured then constrain this
		 * substream to match it. */
		if (twl4030->configured)
			twl4030_constraints(twl4030, twl4030->master_substream);
	} else {
		if (!(twl4030_read_reg_cache(codec, TWL4030_REG_CODEC_MODE) &
			TWL4030_OPTION_1)) {
			/* In option2 4 channel is not supported, set the
			 * constraint for the first stream for channels, the
			 * second stream will 'inherit' this cosntraint */
			snd_pcm_hw_constraint_minmax(substream->runtime,
						SNDRV_PCM_HW_PARAM_CHANNELS,
						2, 2);
		}
		twl4030->master_substream = substream;
	}

	return 0;
}