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
struct TYPE_2__ {int cmd; int time; } ;
union evrec {int echo; TYPE_1__ t; } ;
typedef  int /*<<< orphan*/  tmp ;
struct snd_seq_event {int dummy; } ;
struct seq_oss_devinfo {int /*<<< orphan*/  timer; int /*<<< orphan*/  seq_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int SEQ_ECHO ; 
 int /*<<< orphan*/  SNDRV_SEQ_OSS_MODE_MUSIC ; 
#define  TMR_CONTINUE 131 
#define  TMR_ECHO 130 
#define  TMR_STOP 129 
#define  TMR_TEMPO 128 
 int /*<<< orphan*/  memset (union evrec*,int /*<<< orphan*/ ,int) ; 
 int set_echo_event (struct seq_oss_devinfo*,union evrec*,struct snd_seq_event*) ; 
 int snd_seq_oss_timer_continue (int /*<<< orphan*/ ) ; 
 int snd_seq_oss_timer_stop (int /*<<< orphan*/ ) ; 
 int snd_seq_oss_timer_tempo (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
timing_event(struct seq_oss_devinfo *dp, union evrec *q, struct snd_seq_event *ev)
{
	switch (q->t.cmd) {
	case TMR_ECHO:
		if (dp->seq_mode == SNDRV_SEQ_OSS_MODE_MUSIC)
			return set_echo_event(dp, q, ev);
		else {
			union evrec tmp;
			memset(&tmp, 0, sizeof(tmp));
			/* XXX: only for little-endian! */
			tmp.echo = (q->t.time << 8) | SEQ_ECHO;
			return set_echo_event(dp, &tmp, ev);
		} 

	case TMR_STOP:
		if (dp->seq_mode)
			return snd_seq_oss_timer_stop(dp->timer);
		return 0;

	case TMR_CONTINUE:
		if (dp->seq_mode)
			return snd_seq_oss_timer_continue(dp->timer);
		return 0;

	case TMR_TEMPO:
		if (dp->seq_mode)
			return snd_seq_oss_timer_tempo(dp->timer, q->t.time);
		return 0;
	}

	return -EINVAL;
}