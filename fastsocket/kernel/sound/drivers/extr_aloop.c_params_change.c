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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {unsigned long long format; int /*<<< orphan*/  channels; int /*<<< orphan*/  rate; struct loopback_pcm* private_data; } ;
struct loopback_pcm {struct loopback_cable* cable; } ;
struct TYPE_2__ {unsigned long long formats; int /*<<< orphan*/  channels_max; int /*<<< orphan*/  channels_min; int /*<<< orphan*/  rate_max; int /*<<< orphan*/  rate_min; } ;
struct loopback_cable {int /*<<< orphan*/ * streams; TYPE_1__ hw; } ;

/* Variables and functions */
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  params_change_substream (int /*<<< orphan*/ ,struct snd_pcm_runtime*) ; 

__attribute__((used)) static void params_change(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct loopback_pcm *dpcm = runtime->private_data;
	struct loopback_cable *cable = dpcm->cable;

	cable->hw.formats = (1ULL << runtime->format);
	cable->hw.rate_min = runtime->rate;
	cable->hw.rate_max = runtime->rate;
	cable->hw.channels_min = runtime->channels;
	cable->hw.channels_max = runtime->channels;
	params_change_substream(cable->streams[SNDRV_PCM_STREAM_PLAYBACK],
				runtime);
	params_change_substream(cable->streams[SNDRV_PCM_STREAM_CAPTURE],
				runtime);
}