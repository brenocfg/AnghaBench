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
struct seq_oss_timer {int running; int /*<<< orphan*/  dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_CONTINUE ; 
 int /*<<< orphan*/  send_timer_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
snd_seq_oss_timer_continue(struct seq_oss_timer *timer)
{
	if (timer->running)
		return 0;
	send_timer_event(timer->dp, SNDRV_SEQ_EVENT_CONTINUE, 0);
	timer->running = 1;
	return 0;
}