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
struct snd_seq_timer {int running; int /*<<< orphan*/  last_update; int /*<<< orphan*/  ticks; int /*<<< orphan*/  timeri; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 scalar_t__ initialize_timer (struct snd_seq_timer*) ; 
 int /*<<< orphan*/  snd_seq_timer_reset (struct snd_seq_timer*) ; 
 int /*<<< orphan*/  snd_seq_timer_stop (struct snd_seq_timer*) ; 
 int /*<<< orphan*/  snd_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int snd_seq_timer_start(struct snd_seq_timer * tmr)
{
	if (! tmr->timeri)
		return -EINVAL;
	if (tmr->running)
		snd_seq_timer_stop(tmr);
	snd_seq_timer_reset(tmr);
	if (initialize_timer(tmr) < 0)
		return -EINVAL;
	snd_timer_start(tmr->timeri, tmr->ticks);
	tmr->running = 1;
	do_gettimeofday(&tmr->last_update);
	return 0;
}