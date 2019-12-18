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
struct seq_oss_timer {int /*<<< orphan*/  cur_tick; } ;
typedef  int /*<<< orphan*/  abstime_t ;

/* Variables and functions */

__attribute__((used)) static inline abstime_t
snd_seq_oss_timer_cur_tick(struct seq_oss_timer *timer)
{
	return timer->cur_tick;
}