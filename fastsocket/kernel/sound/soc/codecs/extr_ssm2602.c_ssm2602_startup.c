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
struct ssm2602_priv {struct snd_pcm_substream* master_substream; struct snd_pcm_substream* slave_substream; } ;
struct snd_soc_pcm_runtime {struct snd_soc_device* socdev; } ;
struct snd_soc_device {TYPE_1__* card; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_soc_codec {struct i2c_client* control_data; struct ssm2602_priv* private_data; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_runtime {scalar_t__ sample_bits; scalar_t__ rate; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct snd_soc_codec* codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_SAMPLE_BITS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_minmax (struct snd_pcm_runtime*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ssm2602_startup(struct snd_pcm_substream *substream,
			   struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_device *socdev = rtd->socdev;
	struct snd_soc_codec *codec = socdev->card->codec;
	struct ssm2602_priv *ssm2602 = codec->private_data;
	struct i2c_client *i2c = codec->control_data;
	struct snd_pcm_runtime *master_runtime;

	/* The DAI has shared clocks so if we already have a playback or
	 * capture going then constrain this substream to match it.
	 * TODO: the ssm2602 allows pairs of non-matching PB/REC rates
	 */
	if (ssm2602->master_substream) {
		master_runtime = ssm2602->master_substream->runtime;
		dev_dbg(&i2c->dev, "Constraining to %d bits at %dHz\n",
			master_runtime->sample_bits,
			master_runtime->rate);

		if (master_runtime->rate != 0)
			snd_pcm_hw_constraint_minmax(substream->runtime,
						     SNDRV_PCM_HW_PARAM_RATE,
						     master_runtime->rate,
						     master_runtime->rate);

		if (master_runtime->sample_bits != 0)
			snd_pcm_hw_constraint_minmax(substream->runtime,
						     SNDRV_PCM_HW_PARAM_SAMPLE_BITS,
						     master_runtime->sample_bits,
						     master_runtime->sample_bits);

		ssm2602->slave_substream = substream;
	} else
		ssm2602->master_substream = substream;

	return 0;
}