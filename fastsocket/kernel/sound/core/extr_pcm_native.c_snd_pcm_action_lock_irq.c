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
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct snd_pcm_substream {TYPE_2__ self_group; TYPE_1__* group; } ;
struct action_ops {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_irq (int /*<<< orphan*/ *) ; 
 int snd_pcm_action_group (struct action_ops*,struct snd_pcm_substream*,int,int) ; 
 int snd_pcm_action_single (struct action_ops*,struct snd_pcm_substream*,int) ; 
 int /*<<< orphan*/  snd_pcm_link_rwlock ; 
 scalar_t__ snd_pcm_stream_linked (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_pcm_action_lock_irq(struct action_ops *ops,
				   struct snd_pcm_substream *substream,
				   int state)
{
	int res;

	read_lock_irq(&snd_pcm_link_rwlock);
	if (snd_pcm_stream_linked(substream)) {
		spin_lock(&substream->group->lock);
		spin_lock(&substream->self_group.lock);
		res = snd_pcm_action_group(ops, substream, state, 1);
		spin_unlock(&substream->self_group.lock);
		spin_unlock(&substream->group->lock);
	} else {
		spin_lock(&substream->self_group.lock);
		res = snd_pcm_action_single(ops, substream, state);
		spin_unlock(&substream->self_group.lock);
	}
	read_unlock_irq(&snd_pcm_link_rwlock);
	return res;
}