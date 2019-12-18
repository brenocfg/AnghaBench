#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_1__* pcm; } ;
struct TYPE_4__ {scalar_t__ data; } ;
struct snd_card_aica {int /*<<< orphan*/  channel; TYPE_2__ timer; } ;
struct TYPE_3__ {struct snd_card_aica* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  aica_queue ; 
 int /*<<< orphan*/  del_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spu_disable () ; 

__attribute__((used)) static int snd_aicapcm_pcm_close(struct snd_pcm_substream
				 *substream)
{
	struct snd_card_aica *dreamcastcard = substream->pcm->private_data;
	flush_workqueue(aica_queue);
	if (dreamcastcard->timer.data)
		del_timer(&dreamcastcard->timer);
	kfree(dreamcastcard->channel);
	spu_disable();
	return 0;
}