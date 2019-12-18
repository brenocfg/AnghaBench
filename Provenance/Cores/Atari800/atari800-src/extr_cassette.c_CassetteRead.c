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
 int FALSE ; 
 int /*<<< orphan*/  IMG_TAPE_Read (int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int POKEY_SKCTL ; 
 int TRUE ; 
 int /*<<< orphan*/  UpdateFlags () ; 
 int /*<<< orphan*/  cassette_file ; 
 scalar_t__ cassette_readable ; 
 int eof_of_tape ; 
 scalar_t__ event_time_left ; 
 int /*<<< orphan*/  passing_gap ; 
 int pending_serin ; 
 int /*<<< orphan*/  pending_serin_byte ; 
 int /*<<< orphan*/  serin_byte ; 

__attribute__((used)) static int CassetteRead(int num_ticks)
{
	if (cassette_readable) {
		int loaded = FALSE; /* Function's return value */
		event_time_left -= num_ticks;
		while (event_time_left < 0) {
			unsigned int length;
			if (!passing_gap && pending_serin) {
				serin_byte = pending_serin_byte;
				/* A byte is loaded, return TRUE so it gets stored in POKEY_SERIN. */
				loaded = TRUE;
			}

			/* If POKEY is in reset state, no serial I/O occurs. */
			pending_serin = (POKEY_SKCTL & 0x03) != 0;

			if (!IMG_TAPE_Read(cassette_file, &length, &passing_gap, &pending_serin_byte)) {
				eof_of_tape = 1;
				UpdateFlags();
				return loaded;
			}

			event_time_left += length;
		}
		return loaded;
	}
	return FALSE;
}