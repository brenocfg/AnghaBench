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
struct TYPE_2__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct snd_emux {int client; scalar_t__ timer_active; TYPE_1__ tlist; scalar_t__ use_time; scalar_t__ max_voices; int /*<<< orphan*/ * oss_synth; int /*<<< orphan*/  register_mutex; int /*<<< orphan*/  voice_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 struct snd_emux* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_emux_timer_callback ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int snd_emux_new(struct snd_emux **remu)
{
	struct snd_emux *emu;

	*remu = NULL;
	emu = kzalloc(sizeof(*emu), GFP_KERNEL);
	if (emu == NULL)
		return -ENOMEM;

	spin_lock_init(&emu->voice_lock);
	mutex_init(&emu->register_mutex);

	emu->client = -1;
#ifdef CONFIG_SND_SEQUENCER_OSS
	emu->oss_synth = NULL;
#endif
	emu->max_voices = 0;
	emu->use_time = 0;

	init_timer(&emu->tlist);
	emu->tlist.function = snd_emux_timer_callback;
	emu->tlist.data = (unsigned long)emu;
	emu->timer_active = 0;

	*remu = emu;
	return 0;
}