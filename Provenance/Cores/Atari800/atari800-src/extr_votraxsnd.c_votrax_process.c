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
typedef  int SWORD ;

/* Variables and functions */
 int /*<<< orphan*/  Votrax_Update (int /*<<< orphan*/ ,int*,int) ; 
 double ratio ; 

__attribute__((used)) static void votrax_process(SWORD *v_buffer, int len, SWORD *temp_v_buffer)
{
	static SWORD last_sample;
	static SWORD last_sample2;
	static double startpos;
	static int have;
	int max_left_sample_index = (int)(startpos + (double)(len - 1)*ratio);
	int pos = 0;
	double fraction = 0;
	int i;
	int floor_next_pos;

	if (have == 2) {
	    temp_v_buffer[0] = last_sample;
		temp_v_buffer[1] = last_sample2;
		Votrax_Update(0, temp_v_buffer + 2, (max_left_sample_index + 1 + 1) - 2);
	}
	else if (have == 1) {
	    temp_v_buffer[0] = last_sample;
		Votrax_Update(0, temp_v_buffer + 1, (max_left_sample_index + 1 + 1) - 1);
	}
	else if (have == 0) {
		Votrax_Update(0, temp_v_buffer, max_left_sample_index + 1 + 1);
	}
	else if (have < 0) {
		Votrax_Update(0, temp_v_buffer, -have);
		Votrax_Update(0, temp_v_buffer, max_left_sample_index + 1 + 1);
	}

	for (i = 0; i < len; i++) {
		SWORD left_sample;
		SWORD right_sample;
		SWORD interp_sample;
		pos = (int)(startpos + (double)i*ratio);
		fraction = startpos + (double)i*ratio - (double)pos;
		left_sample = temp_v_buffer[pos];
		right_sample = temp_v_buffer[pos+1];
		interp_sample = (int)(left_sample + fraction*(double)(right_sample-left_sample));
		v_buffer[i] = interp_sample;
	}
	floor_next_pos = (int)(startpos + (double)len*ratio);
	startpos = (startpos + (double)len*ratio) - (double)floor_next_pos;
	if (floor_next_pos == max_left_sample_index)
	{
		have = 2;
		last_sample = temp_v_buffer[floor_next_pos];
		last_sample2 = temp_v_buffer[floor_next_pos+1];
	}
	else if (floor_next_pos == max_left_sample_index + 1) {
		have = 1;
		last_sample = temp_v_buffer[floor_next_pos];
	}
	else {
		have = (floor_next_pos - (max_left_sample_index + 2));
	}
}