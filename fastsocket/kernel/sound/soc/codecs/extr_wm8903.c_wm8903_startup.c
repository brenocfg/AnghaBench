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
struct wm8903_priv {struct snd_pcm_substream* master_substream; struct snd_pcm_substream* slave_substream; int /*<<< orphan*/  capture_active; int /*<<< orphan*/  playback_active; } ;
struct snd_soc_pcm_runtime {struct snd_soc_device* socdev; } ;
struct snd_soc_device {TYPE_1__* card; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_soc_codec {struct i2c_client* control_data; struct wm8903_priv* private_data; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  sample_bits; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct snd_soc_codec* codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_SAMPLE_BITS ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_minmax (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8903_startup(struct snd_pcm_substream *substream,
			  struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_device *socdev = rtd->socdev;
	struct snd_soc_codec *codec = socdev->card->codec;
	struct wm8903_priv *wm8903 = codec->private_data;
	struct i2c_client *i2c = codec->control_data;
	struct snd_pcm_runtime *master_runtime;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		wm8903->playback_active++;
	else
		wm8903->capture_active++;

	/* The DAI has shared clocks so if we already have a playback or
	 * capture going then constrain this substream to match it.
	 */
	if (wm8903->master_substream) {
		master_runtime = wm8903->master_substream->runtime;

		dev_dbg(&i2c->dev, "Constraining to %d bits\n",
			master_runtime->sample_bits);

		snd_pcm_hw_constraint_minmax(substream->runtime,
					     SNDRV_PCM_HW_PARAM_SAMPLE_BITS,
					     master_runtime->sample_bits,
					     master_runtime->sample_bits);

		wm8903->slave_substream = substream;
	} else
		wm8903->master_substream = substream;

	return 0;
}