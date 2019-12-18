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
typedef  scalar_t__ UBYTE ;
typedef  scalar_t__ SWORD ;

/* Variables and functions */
 double MAX_SAMPLE ; 
 double M_PI ; 
 int POKEYSND_BIT16 ; 
 scalar_t__* POKEYSND_process_buffer ; 
 int POKEYSND_process_buffer_fill ; 
 int POKEYSND_process_buffer_length ; 
 int POKEYSND_snd_flags ; 
 double RAND_MAX ; 
 int /*<<< orphan*/  advance_ticks (scalar_t__,unsigned int) ; 
 scalar_t__ floor (double) ; 
 double interp_read_resam_all (scalar_t__,unsigned int) ; 
 double modf (double,double*) ; 
 unsigned int num_cur_pokeys ; 
 scalar_t__ pokey_states ; 
 double rand () ; 
 unsigned int samp_pos ; 
 unsigned int ticks_per_sample ; 

__attribute__((used)) static void generate_sync(unsigned int num_ticks)
{
	double new_samp_pos;
	unsigned int ticks;
	UBYTE *buffer = POKEYSND_process_buffer + POKEYSND_process_buffer_fill;
	UBYTE *buffer_end = POKEYSND_process_buffer + POKEYSND_process_buffer_length;
	unsigned int i;

	for (;;) {
		double int_part;
		new_samp_pos = samp_pos + ticks_per_sample;
		new_samp_pos = modf(new_samp_pos, &int_part);
		ticks = (unsigned int)int_part;
		if (ticks > num_ticks) {
			samp_pos -= num_ticks;
			break;
		}
		if (buffer >= buffer_end)
			break;

		samp_pos = new_samp_pos;
		num_ticks -= ticks;

		for (i = 0; i < num_cur_pokeys; ++i) {
			/* advance pokey to the new position and produce a sample */
			advance_ticks(pokey_states + i, ticks);
			if (POKEYSND_snd_flags & POKEYSND_BIT16) {
				*((SWORD *)buffer) = (SWORD)floor(
					(interp_read_resam_all(pokey_states + i, samp_pos) - MAX_SAMPLE / 2.0)
					* (65535.0 / MAX_SAMPLE / 4 * M_PI * 0.95)
					+ 0.5 + 0.5 * rand() / RAND_MAX - 0.25
				);
				buffer += 2;
			}
			else
				*buffer++ = (UBYTE)floor(
					(interp_read_resam_all(pokey_states + i, samp_pos) - MAX_SAMPLE / 2.0)
					* (255.0 / MAX_SAMPLE / 4 * M_PI * 0.95)
					+ 128 + 0.5 + 0.5 * rand() / RAND_MAX - 0.25
				);
		}
	}

	POKEYSND_process_buffer_fill = buffer - POKEYSND_process_buffer;
	if (num_ticks > 0) {
		/* remaining ticks */
		for (i = 0; i < num_cur_pokeys; ++i)
			advance_ticks(pokey_states + i, num_ticks);
	}
}