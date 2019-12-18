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
struct midi_input_info {int m_state; int m_ptr; int m_left; unsigned char* m_buf; unsigned char m_prev_status; } ;
struct TYPE_2__ {struct midi_input_info in_info; } ;

/* Variables and functions */
#define  MST_DATA 130 
#define  MST_INIT 129 
#define  MST_SYSEX 128 
 int /*<<< orphan*/  do_midi_msg (int,unsigned char*,int) ; 
 int* midi2synth ; 
 TYPE_1__** midi_devs ; 
 int num_midis ; 
 int /*<<< orphan*/  printk (char*,int,int,int) ; 

__attribute__((used)) static void
midi_synth_input(int orig_dev, unsigned char data)
{
	int             dev;
	struct midi_input_info *inc;

	static unsigned char len_tab[] =	/* # of data bytes following a status
						 */
	{
		2,		/* 8x */
		2,		/* 9x */
		2,		/* Ax */
		2,		/* Bx */
		1,		/* Cx */
		1,		/* Dx */
		2,		/* Ex */
		0		/* Fx */
	};

	if (orig_dev < 0 || orig_dev > num_midis || midi_devs[orig_dev] == NULL)
		return;

	if (data == 0xfe)	/* Ignore active sensing */
		return;

	dev = midi2synth[orig_dev];
	inc = &midi_devs[orig_dev]->in_info;

	switch (inc->m_state)
	  {
	  case MST_INIT:
		  if (data & 0x80)	/* MIDI status byte */
		    {
			    if ((data & 0xf0) == 0xf0)	/* Common message */
			      {
				      switch (data)
					{
					case 0xf0:	/* Sysex */
						inc->m_state = MST_SYSEX;
						break;	/* Sysex */

					case 0xf1:	/* MTC quarter frame */
					case 0xf3:	/* Song select */
						inc->m_state = MST_DATA;
						inc->m_ptr = 1;
						inc->m_left = 1;
						inc->m_buf[0] = data;
						break;

					case 0xf2:	/* Song position pointer */
						inc->m_state = MST_DATA;
						inc->m_ptr = 1;
						inc->m_left = 2;
						inc->m_buf[0] = data;
						break;

					default:
						inc->m_buf[0] = data;
						inc->m_ptr = 1;
						do_midi_msg(dev, inc->m_buf, inc->m_ptr);
						inc->m_ptr = 0;
						inc->m_left = 0;
					}
			    } else
			      {
				      inc->m_state = MST_DATA;
				      inc->m_ptr = 1;
				      inc->m_left = len_tab[(data >> 4) - 8];
				      inc->m_buf[0] = inc->m_prev_status = data;
			      }
		    } else if (inc->m_prev_status & 0x80) {
			    /* Data byte (use running status) */
			    inc->m_ptr = 2;
			    inc->m_buf[1] = data;
			    inc->m_buf[0] = inc->m_prev_status;
			    inc->m_left = len_tab[(inc->m_buf[0] >> 4) - 8] - 1;
			    if (inc->m_left > 0)
				    inc->m_state = MST_DATA; /* Not done yet */
			    else {
				    inc->m_state = MST_INIT;
				    do_midi_msg(dev, inc->m_buf, inc->m_ptr);
				    inc->m_ptr = 0;
			    }
		    }
		  break;	/* MST_INIT */

	  case MST_DATA:
		  inc->m_buf[inc->m_ptr++] = data;
		  if (--inc->m_left <= 0)
		    {
			    inc->m_state = MST_INIT;
			    do_midi_msg(dev, inc->m_buf, inc->m_ptr);
			    inc->m_ptr = 0;
		    }
		  break;	/* MST_DATA */

	  case MST_SYSEX:
		  if (data == 0xf7)	/* Sysex end */
		    {
			    inc->m_state = MST_INIT;
			    inc->m_left = 0;
			    inc->m_ptr = 0;
		    }
		  break;	/* MST_SYSEX */

	  default:
		  printk("MIDI%d: Unexpected state %d (%02x)\n", orig_dev, inc->m_state, (int) data);
		  inc->m_state = MST_INIT;
	  }
}