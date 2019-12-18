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
struct pmac_stream {int dummy; } ;
struct snd_pmac {struct pmac_stream capture; struct pmac_stream playback; } ;

/* Variables and functions */
#define  SNDRV_PCM_STREAM_CAPTURE 129 
#define  SNDRV_PCM_STREAM_PLAYBACK 128 
 int /*<<< orphan*/  snd_BUG () ; 

__attribute__((used)) static struct pmac_stream *snd_pmac_get_stream(struct snd_pmac *chip, int stream)
{
	switch (stream) {
	case SNDRV_PCM_STREAM_PLAYBACK:
		return &chip->playback;
	case SNDRV_PCM_STREAM_CAPTURE:
		return &chip->capture;
	default:
		snd_BUG();
		return NULL;
	}
}