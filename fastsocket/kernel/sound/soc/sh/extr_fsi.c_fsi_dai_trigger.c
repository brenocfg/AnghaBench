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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  period_size; int /*<<< orphan*/  buffer_size; } ;
struct fsi_priv {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  frames_to_bytes (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int fsi_data_push (struct fsi_priv*) ; 
 struct fsi_priv* fsi_get (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  fsi_irq_disable (struct fsi_priv*,int) ; 
 int /*<<< orphan*/  fsi_stream_pop (struct fsi_priv*) ; 
 int /*<<< orphan*/  fsi_stream_push (struct fsi_priv*,struct snd_pcm_substream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsi_dai_trigger(struct snd_pcm_substream *substream, int cmd,
			   struct snd_soc_dai *dai)
{
	struct fsi_priv *fsi = fsi_get(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	int is_play = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	int ret = 0;

	/* capture not supported */
	if (!is_play)
		return -ENODEV;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		fsi_stream_push(fsi, substream,
				frames_to_bytes(runtime, runtime->buffer_size),
				frames_to_bytes(runtime, runtime->period_size));
		ret = fsi_data_push(fsi);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		fsi_irq_disable(fsi, is_play);
		fsi_stream_pop(fsi);
		break;
	}

	return ret;
}