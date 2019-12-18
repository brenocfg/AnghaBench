#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_platform {TYPE_4__* pcm_ops; } ;
struct snd_soc_pcm_runtime {struct snd_soc_dai_link* dai; struct snd_soc_device* socdev; } ;
struct snd_soc_device {struct snd_soc_card* card; } ;
struct snd_soc_dai_link {TYPE_3__* ops; struct snd_soc_dai* codec_dai; struct snd_soc_dai* cpu_dai; } ;
struct TYPE_10__ {scalar_t__ active; int /*<<< orphan*/  stream_name; } ;
struct TYPE_6__ {scalar_t__ active; } ;
struct snd_soc_dai {int pop_wait; TYPE_5__ capture; int /*<<< orphan*/ * runtime; TYPE_2__* ops; scalar_t__ active; TYPE_1__ playback; } ;
struct snd_soc_codec {int /*<<< orphan*/  active; } ;
struct snd_soc_card {int /*<<< orphan*/  delayed_work; struct snd_soc_codec* codec; struct snd_soc_platform* platform; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* close ) (struct snd_pcm_substream*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  (* shutdown ) (struct snd_pcm_substream*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* shutdown ) (struct snd_pcm_substream*,struct snd_soc_dai*) ;} ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  SND_SOC_DAPM_STREAM_STOP ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcm_mutex ; 
 int /*<<< orphan*/  pmdown_time ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dai_digital_mute (struct snd_soc_dai*,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_stream_event (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct snd_pcm_substream*,struct snd_soc_dai*) ; 
 int /*<<< orphan*/  stub2 (struct snd_pcm_substream*,struct snd_soc_dai*) ; 
 int /*<<< orphan*/  stub3 (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  stub4 (struct snd_pcm_substream*) ; 

__attribute__((used)) static int soc_codec_close(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_device *socdev = rtd->socdev;
	struct snd_soc_card *card = socdev->card;
	struct snd_soc_dai_link *machine = rtd->dai;
	struct snd_soc_platform *platform = card->platform;
	struct snd_soc_dai *cpu_dai = machine->cpu_dai;
	struct snd_soc_dai *codec_dai = machine->codec_dai;
	struct snd_soc_codec *codec = card->codec;

	mutex_lock(&pcm_mutex);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		cpu_dai->playback.active = codec_dai->playback.active = 0;
	else
		cpu_dai->capture.active = codec_dai->capture.active = 0;

	if (codec_dai->playback.active == 0 &&
		codec_dai->capture.active == 0) {
		cpu_dai->active = codec_dai->active = 0;
	}
	codec->active--;

	/* Muting the DAC suppresses artifacts caused during digital
	 * shutdown, for example from stopping clocks.
	 */
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		snd_soc_dai_digital_mute(codec_dai, 1);

	if (cpu_dai->ops->shutdown)
		cpu_dai->ops->shutdown(substream, cpu_dai);

	if (codec_dai->ops->shutdown)
		codec_dai->ops->shutdown(substream, codec_dai);

	if (machine->ops && machine->ops->shutdown)
		machine->ops->shutdown(substream);

	if (platform->pcm_ops->close)
		platform->pcm_ops->close(substream);
	cpu_dai->runtime = NULL;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		/* start delayed pop wq here for playback streams */
		codec_dai->pop_wait = 1;
		schedule_delayed_work(&card->delayed_work,
			msecs_to_jiffies(pmdown_time));
	} else {
		/* capture streams can be powered down now */
		snd_soc_dapm_stream_event(codec,
			codec_dai->capture.stream_name,
			SND_SOC_DAPM_STREAM_STOP);
	}

	mutex_unlock(&pcm_mutex);
	return 0;
}