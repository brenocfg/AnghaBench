#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* close ) (int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* bender ) (int,int,int) ;int /*<<< orphan*/  (* controller ) (int,int,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* reset ) (int) ;} ;

/* Variables and functions */
 scalar_t__ SEQ_2 ; 
 scalar_t__ iqhead ; 
 scalar_t__ iqlen ; 
 scalar_t__ iqtail ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  lock ; 
 int max_mididev ; 
 int max_synthdev ; 
 TYPE_2__** midi_devs ; 
 scalar_t__* midi_opened ; 
 int /*<<< orphan*/  midi_outc (int,int) ; 
 scalar_t__* midi_written ; 
 scalar_t__ prev_event_time ; 
 scalar_t__ prev_input_time ; 
 scalar_t__ qhead ; 
 scalar_t__ qlen ; 
 scalar_t__ qtail ; 
 scalar_t__ seq_mode ; 
 scalar_t__ seq_playing ; 
 int /*<<< orphan*/  seq_sleeper ; 
 int /*<<< orphan*/  seq_time ; 
 int /*<<< orphan*/  sound_stop_timer () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int,int) ; 
 int /*<<< orphan*/  stub5 (int) ; 
 TYPE_1__** synth_devs ; 
 int synth_open_mask ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void seq_reset(void)
{
	/*
	 * NOTE! Calls sleep(). Don't call this from interrupt.
	 */

	int i;
	int chn;
	unsigned long flags;

	sound_stop_timer();

	seq_time = jiffies;
	prev_input_time = 0;
	prev_event_time = 0;

	qlen = qhead = qtail = 0;
	iqlen = iqhead = iqtail = 0;

	for (i = 0; i < max_synthdev; i++)
		if (synth_open_mask & (1 << i))
			if (synth_devs[i])
				synth_devs[i]->reset(i);

	if (seq_mode == SEQ_2)
	{
		for (chn = 0; chn < 16; chn++)
			for (i = 0; i < max_synthdev; i++)
				if (synth_open_mask & (1 << i))
					if (synth_devs[i])
					{
						synth_devs[i]->controller(i, chn, 123, 0);	/* All notes off */
						synth_devs[i]->controller(i, chn, 121, 0);	/* Reset all ctl */
						synth_devs[i]->bender(i, chn, 1 << 13);	/* Bender off */
					}
	}
	else	/* seq_mode == SEQ_1 */
	{
		for (i = 0; i < max_mididev; i++)
			if (midi_written[i])	/*
						 * Midi used. Some notes may still be playing
						 */
			{
				/*
				 *      Sending just a ACTIVE SENSING message should be enough to stop all
				 *      playing notes. Since there are devices not recognizing the
				 *      active sensing, we have to send some all notes off messages also.
				 */
				midi_outc(i, 0xfe);

				for (chn = 0; chn < 16; chn++)
				{
					midi_outc(i, (unsigned char) (0xb0 + (chn & 0x0f)));		/* control change */
					midi_outc(i, 0x7b);	/* All notes off */
					midi_outc(i, 0);	/* Dummy parameter */
				}

				midi_devs[i]->close(i);

				midi_written[i] = 0;
				midi_opened[i] = 0;
			}
	}

	seq_playing = 0;

	spin_lock_irqsave(&lock,flags);

	if (waitqueue_active(&seq_sleeper)) {
		/*      printk( "Sequencer Warning: Unexpected sleeping process - Waking up\n"); */
		wake_up(&seq_sleeper);
	}
	spin_unlock_irqrestore(&lock,flags);
}