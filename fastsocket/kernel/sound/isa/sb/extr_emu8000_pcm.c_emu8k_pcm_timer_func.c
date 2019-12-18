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
struct TYPE_2__ {scalar_t__ expires; } ;
struct snd_emu8k_pcm {int last_ptr; int buf_size; int period_pos; int period_size; int /*<<< orphan*/  timer_lock; int /*<<< orphan*/  substream; TYPE_1__ timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int emu8k_get_curpos (struct snd_emu8k_pcm*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void emu8k_pcm_timer_func(unsigned long data)
{
	struct snd_emu8k_pcm *rec = (struct snd_emu8k_pcm *)data;
	int ptr, delta;

	spin_lock(&rec->timer_lock);
	/* update the current pointer */
	ptr = emu8k_get_curpos(rec, 0);
	if (ptr < rec->last_ptr)
		delta = ptr + rec->buf_size - rec->last_ptr;
	else
		delta = ptr - rec->last_ptr;
	rec->period_pos += delta;
	rec->last_ptr = ptr;

	/* reprogram timer */
	rec->timer.expires = jiffies + 1;
	add_timer(&rec->timer);

	/* update period */
	if (rec->period_pos >= (int)rec->period_size) {
		rec->period_pos %= rec->period_size;
		spin_unlock(&rec->timer_lock);
		snd_pcm_period_elapsed(rec->substream);
		return;
	}
	spin_unlock(&rec->timer_lock);
}