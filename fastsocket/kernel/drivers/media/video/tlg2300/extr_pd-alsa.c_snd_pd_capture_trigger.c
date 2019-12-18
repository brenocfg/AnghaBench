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
struct snd_pcm_substream {int dummy; } ;
struct poseidon_audio {int /*<<< orphan*/  capture_stream; int /*<<< orphan*/  copied_position; int /*<<< orphan*/  rcv_position; } ;
struct poseidon {struct poseidon_audio audio; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  STREAM_OFF ; 
 int /*<<< orphan*/  STREAM_ON ; 
 int /*<<< orphan*/  STREAM_SUSPEND ; 
 scalar_t__ debug_mode ; 
 int /*<<< orphan*/  fire_audio_urb (struct poseidon*) ; 
 int /*<<< orphan*/  in_hibernation (struct poseidon*) ; 
 int /*<<< orphan*/  log (char*,int,int /*<<< orphan*/ ) ; 
 struct poseidon* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_pd_capture_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct poseidon *p = snd_pcm_substream_chip(substream);
	struct poseidon_audio *pa = &p->audio;

	if (debug_mode)
		log("cmd %d, audio stat : %d\n", cmd, pa->capture_stream);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_START:
		if (pa->capture_stream == STREAM_ON)
			return 0;

		pa->rcv_position = pa->copied_position = 0;
		pa->capture_stream = STREAM_ON;

		if (in_hibernation(p))
			return 0;
		fire_audio_urb(p);
		return 0;

	case SNDRV_PCM_TRIGGER_SUSPEND:
		pa->capture_stream = STREAM_SUSPEND;
		return 0;
	case SNDRV_PCM_TRIGGER_STOP:
		pa->capture_stream = STREAM_OFF;
		return 0;
	default:
		return -EINVAL;
	}
}