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
struct mpu_config {int devno; int /*<<< orphan*/  timer_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEQ_CONTINUE_TIMER () ; 
 int /*<<< orphan*/  SEQ_SONGPOS (int) ; 
 int /*<<< orphan*/  SEQ_START_TIMER () ; 
 int /*<<< orphan*/  SEQ_STOP_TIMER () ; 
 int /*<<< orphan*/  STORE (int /*<<< orphan*/ ) ; 
#define  TMR_CLOCK 132 
#define  TMR_CONTINUE 131 
 int TMR_EXTERNAL ; 
#define  TMR_SPP 130 
#define  TMR_START 129 
#define  TMR_STOP 128 
 int /*<<< orphan*/  next_event_time ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  setup_metronome (int) ; 
 int /*<<< orphan*/  stop_metronome (int) ; 
 int timer_mode ; 
 int tmr_running ; 

__attribute__((used)) static void timer_ext_event(struct mpu_config *devc, int event, int parm)
{
	int midi_dev = devc->devno;

	if (!devc->timer_flag)
		return;

	switch (event)
	{
		case TMR_CLOCK:
			printk("<MIDI clk>");
			break;

		case TMR_START:
			printk("Ext MIDI start\n");
			if (!tmr_running)
			{
				if (timer_mode & TMR_EXTERNAL)
				{
					tmr_running = 1;
					setup_metronome(midi_dev);
					next_event_time = 0;
					STORE(SEQ_START_TIMER());
				}
			}
			break;

		case TMR_STOP:
			printk("Ext MIDI stop\n");
			if (timer_mode & TMR_EXTERNAL)
			{
				tmr_running = 0;
				stop_metronome(midi_dev);
				STORE(SEQ_STOP_TIMER());
			}
			break;

		case TMR_CONTINUE:
			printk("Ext MIDI continue\n");
			if (timer_mode & TMR_EXTERNAL)
			{
				tmr_running = 1;
				setup_metronome(midi_dev);
				STORE(SEQ_CONTINUE_TIMER());
		  	}
		  	break;

		case TMR_SPP:
			printk("Songpos: %d\n", parm);
			if (timer_mode & TMR_EXTERNAL)
			{
				STORE(SEQ_SONGPOS(parm));
			}
			break;
	}
}