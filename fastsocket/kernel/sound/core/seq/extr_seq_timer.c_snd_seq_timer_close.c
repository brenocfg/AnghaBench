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
struct snd_seq_timer {int /*<<< orphan*/ * timeri; } ;
struct snd_seq_queue {struct snd_seq_timer* timer; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_timer_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_timer_stop (int /*<<< orphan*/ *) ; 

int snd_seq_timer_close(struct snd_seq_queue *q)
{
	struct snd_seq_timer *tmr;
	
	tmr = q->timer;
	if (snd_BUG_ON(!tmr))
		return -EINVAL;
	if (tmr->timeri) {
		snd_timer_stop(tmr->timeri);
		snd_timer_close(tmr->timeri);
		tmr->timeri = NULL;
	}
	return 0;
}