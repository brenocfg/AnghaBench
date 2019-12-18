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
struct TYPE_2__ {scalar_t__ (* outputc ) (int,unsigned char) ;} ;

/* Variables and functions */
 TYPE_1__** midi_devs ; 
 unsigned char* prev_out_status ; 
 int /*<<< orphan*/  printk (char*) ; 
 scalar_t__ stub1 (int,unsigned char) ; 

__attribute__((used)) static void
midi_outc(int midi_dev, int data)
{
	int             timeout;

	for (timeout = 0; timeout < 3200; timeout++)
		if (midi_devs[midi_dev]->outputc(midi_dev, (unsigned char) (data & 0xff)))
		  {
			  if (data & 0x80)	/*
						 * Status byte
						 */
				  prev_out_status[midi_dev] =
				      (unsigned char) (data & 0xff);	/*
									 * Store for running status
									 */
			  return;	/*
					 * Mission complete
					 */
		  }
	/*
	 * Sorry! No space on buffers.
	 */
	printk("Midi send timed out\n");
}