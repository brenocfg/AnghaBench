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
struct em28xx {int /*<<< orphan*/  wq_trigger; int /*<<< orphan*/  stream_started; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct em28xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_em28xx_capture_trigger(struct snd_pcm_substream *substream,
				      int cmd)
{
	struct em28xx *dev = snd_pcm_substream_chip(substream);
	int retval;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		atomic_set(&dev->stream_started, 1);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		atomic_set(&dev->stream_started, 1);
		break;
	default:
		retval = -EINVAL;
	}
	schedule_work(&dev->wq_trigger);
	return 0;
}