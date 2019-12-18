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
struct seq_oss_timer {int oss_tempo; int oss_timebase; scalar_t__ running; scalar_t__ realtime; scalar_t__ cur_tick; struct seq_oss_devinfo* dp; } ;
struct seq_oss_devinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  calc_alsa_tempo (struct seq_oss_timer*) ; 
 struct seq_oss_timer* kzalloc (int,int /*<<< orphan*/ ) ; 

struct seq_oss_timer *
snd_seq_oss_timer_new(struct seq_oss_devinfo *dp)
{
	struct seq_oss_timer *rec;

	rec = kzalloc(sizeof(*rec), GFP_KERNEL);
	if (rec == NULL)
		return NULL;

	rec->dp = dp;
	rec->cur_tick = 0;
	rec->realtime = 0;
	rec->running = 0;
	rec->oss_tempo = 60;
	rec->oss_timebase = 100;
	calc_alsa_tempo(rec);

	return rec;
}