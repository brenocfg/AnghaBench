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
struct rme96 {struct snd_pcm_substream* playback_substream; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  RME96_ISPLAYING (struct rme96*) ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 131 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 130 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 struct rme96* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_rme96_playback_start (struct rme96*,int) ; 
 int /*<<< orphan*/  snd_rme96_playback_stop (struct rme96*) ; 

__attribute__((used)) static int
snd_rme96_playback_trigger(struct snd_pcm_substream *substream, 
			   int cmd)
{
	struct rme96 *rme96 = snd_pcm_substream_chip(substream);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		if (!RME96_ISPLAYING(rme96)) {
			if (substream != rme96->playback_substream) {
				return -EBUSY;
			}
			snd_rme96_playback_start(rme96, 0);
		}
		break;

	case SNDRV_PCM_TRIGGER_STOP:
		if (RME96_ISPLAYING(rme96)) {
			if (substream != rme96->playback_substream) {
				return -EBUSY;
			}
			snd_rme96_playback_stop(rme96);
		}
		break;

	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		if (RME96_ISPLAYING(rme96)) {
			snd_rme96_playback_stop(rme96);
		}
		break;

	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		if (!RME96_ISPLAYING(rme96)) {
			snd_rme96_playback_start(rme96, 1);
		}
		break;
		
	default:
		return -EINVAL;
	}
	return 0;
}