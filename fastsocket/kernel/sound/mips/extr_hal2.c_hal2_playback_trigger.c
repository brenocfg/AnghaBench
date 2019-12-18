#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_3__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw_data; int /*<<< orphan*/  hw_io; } ;
struct TYPE_5__ {TYPE_1__ pcm_indirect; int /*<<< orphan*/  buffer_dma; } ;
struct snd_hal2 {TYPE_2__ dac; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* ack ) (struct snd_pcm_substream*) ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  hal2_start_dac (struct snd_hal2*) ; 
 int /*<<< orphan*/  hal2_stop_dac (struct snd_hal2*) ; 
 struct snd_hal2* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  stub1 (struct snd_pcm_substream*) ; 

__attribute__((used)) static int hal2_playback_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_hal2 *hal2 = snd_pcm_substream_chip(substream);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		hal2->dac.pcm_indirect.hw_io = hal2->dac.buffer_dma;
		hal2->dac.pcm_indirect.hw_data = 0;
		substream->ops->ack(substream);
		hal2_start_dac(hal2);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		hal2_stop_dac(hal2);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}