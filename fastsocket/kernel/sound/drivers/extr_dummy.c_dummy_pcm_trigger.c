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
struct snd_pcm_substream {int dummy; } ;
struct snd_dummy {TYPE_1__* timer_ops; } ;
struct TYPE_2__ {int (* start ) (struct snd_pcm_substream*) ;int (* stop ) (struct snd_pcm_substream*) ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 struct snd_dummy* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int stub1 (struct snd_pcm_substream*) ; 
 int stub2 (struct snd_pcm_substream*) ; 

__attribute__((used)) static int dummy_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_dummy *dummy = snd_pcm_substream_chip(substream);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		return dummy->timer_ops->start(substream);
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		return dummy->timer_ops->stop(substream);
	}
	return -EINVAL;
}