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
struct wm8903_priv {struct snd_pcm_substream* slave_substream; struct snd_pcm_substream* master_substream; int /*<<< orphan*/  capture_active; int /*<<< orphan*/  playback_active; } ;
struct snd_soc_pcm_runtime {struct snd_soc_device* socdev; } ;
struct snd_soc_device {TYPE_1__* card; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_soc_codec {struct wm8903_priv* private_data; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_2__ {struct snd_soc_codec* codec; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 

__attribute__((used)) static void wm8903_shutdown(struct snd_pcm_substream *substream,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_device *socdev = rtd->socdev;
	struct snd_soc_codec *codec = socdev->card->codec;
	struct wm8903_priv *wm8903 = codec->private_data;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		wm8903->playback_active--;
	else
		wm8903->capture_active--;

	if (wm8903->master_substream == substream)
		wm8903->master_substream = wm8903->slave_substream;

	wm8903->slave_substream = NULL;
}