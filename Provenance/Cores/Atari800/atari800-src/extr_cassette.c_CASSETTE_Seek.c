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

/* Variables and functions */
 void* CASSETTE_record ; 
 void* FALSE ; 
 int /*<<< orphan*/  IMG_TAPE_Seek (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  UpdateFlags () ; 
 int /*<<< orphan*/ * cassette_file ; 
 scalar_t__ eof_of_tape ; 
 scalar_t__ event_time_left ; 
 void* passing_gap ; 
 void* pending_serin ; 

void CASSETTE_Seek(unsigned int position)
{
	if (cassette_file != NULL) {
		if (position > 0)
			position --;
		IMG_TAPE_Seek(cassette_file, position);

		event_time_left = 0;
		pending_serin = FALSE;
		passing_gap = FALSE;
		eof_of_tape = 0;
		CASSETTE_record = FALSE;
		UpdateFlags();
	}
}