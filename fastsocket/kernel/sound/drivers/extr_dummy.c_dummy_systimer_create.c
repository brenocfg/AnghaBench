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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct TYPE_4__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct dummy_systimer_pcm {struct snd_pcm_substream* substream; int /*<<< orphan*/  lock; TYPE_2__ timer; } ;
struct TYPE_3__ {struct dummy_systimer_pcm* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dummy_systimer_callback ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 struct dummy_systimer_pcm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dummy_systimer_create(struct snd_pcm_substream *substream)
{
	struct dummy_systimer_pcm *dpcm;

	dpcm = kzalloc(sizeof(*dpcm), GFP_KERNEL);
	if (!dpcm)
		return -ENOMEM;
	substream->runtime->private_data = dpcm;
	init_timer(&dpcm->timer);
	dpcm->timer.data = (unsigned long) dpcm;
	dpcm->timer.function = dummy_systimer_callback;
	spin_lock_init(&dpcm->lock);
	dpcm->substream = substream;
	return 0;
}