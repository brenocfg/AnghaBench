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
struct TYPE_2__ {int (* event ) (int /*<<< orphan*/ ,unsigned char*) ;} ;

/* Variables and functions */
 scalar_t__ SEQ_2 ; 
 unsigned int SEQ_ECHO ; 
 scalar_t__ SEQ_MAX_QUEUE ; 
 int TIMER_ARMED ; 
 int TIMER_NOT_ARMED ; 
#define  TMR_CONTINUE 134 
#define  TMR_ECHO 133 
#define  TMR_START 132 
#define  TMR_STOP 131 
#define  TMR_TEMPO 130 
#define  TMR_WAIT_ABS 129 
#define  TMR_WAIT_REL 128 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ output_threshold ; 
 unsigned int prev_event_time ; 
 int /*<<< orphan*/  prev_input_time ; 
 scalar_t__ qlen ; 
 int /*<<< orphan*/  request_sound_timer (long) ; 
 int /*<<< orphan*/  seq_copy_to_input (unsigned char*,int) ; 
 scalar_t__ seq_mode ; 
 int seq_playing ; 
 int /*<<< orphan*/  seq_sleeper ; 
 int /*<<< orphan*/  seq_time ; 
 int stub1 (int /*<<< orphan*/ ,unsigned char*) ; 
 TYPE_1__* tmr ; 
 int /*<<< orphan*/  tmr_no ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int seq_timing_event(unsigned char *event_rec)
{
	unsigned char cmd = event_rec[1];
	unsigned int parm = *(int *) &event_rec[4];

	if (seq_mode == SEQ_2)
	{
		int ret;

		if ((ret = tmr->event(tmr_no, event_rec)) == TIMER_ARMED)
			if ((SEQ_MAX_QUEUE - qlen) >= output_threshold)
				wake_up(&seq_sleeper);
		return ret;
	}
	switch (cmd)
	{
		case TMR_WAIT_REL:
			parm += prev_event_time;

			/*
			 * NOTE!  No break here. Execution of TMR_WAIT_REL continues in the
			 * next case (TMR_WAIT_ABS)
			 */

		case TMR_WAIT_ABS:
			if (parm > 0)
			{
				long time;

				time = parm;
				prev_event_time = time;

				seq_playing = 1;
				request_sound_timer(time);

				if ((SEQ_MAX_QUEUE - qlen) >= output_threshold)
					wake_up(&seq_sleeper);
				return TIMER_ARMED;
			}
			break;

		case TMR_START:
			seq_time = jiffies;
			prev_input_time = 0;
			prev_event_time = 0;
			break;

		case TMR_STOP:
			break;

		case TMR_CONTINUE:
			break;

		case TMR_TEMPO:
			break;

		case TMR_ECHO:
			if (seq_mode == SEQ_2)
				seq_copy_to_input(event_rec, 8);
			else
			{
				parm = (parm << 8 | SEQ_ECHO);
				seq_copy_to_input((unsigned char *) &parm, 4);
			}
			break;

		default:;
	}

	return TIMER_NOT_ARMED;
}