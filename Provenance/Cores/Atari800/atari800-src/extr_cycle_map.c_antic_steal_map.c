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
 int BITMAP_C ; 
 int CHAR_C ; 
 int DMARE_C ; 
 int DMARS_C ; 
 int END_C ; 
 int FONT_C ; 
 int /*<<< orphan*/  cpu_cycle_map (char*,int*,int*) ; 

__attribute__((used)) static void antic_steal_map(int width, int md, int scroll_offset, int use_char_index,
	int use_font, int use_bitmap, char *antic_cycles, int *cpu_cycles,
	int *actual_cycles)
{
	int char_start;
	int bitmap_start;
	int font_start;
	int i;
	int dram_pending;
	int interval;
	int steal;
	int max_chars;
	/* defaults for wide playfield */
#define CHAR_C 13
#define BITMAP_C (CHAR_C + 2)
#define FONT_C (CHAR_C + 3)
#define END_C (CHAR_C + 95)
#define DMARS_C (CHAR_C + 15)
#define DMARE_C (DMARS_C + 32)
	char_start = CHAR_C + scroll_offset;
	bitmap_start = BITMAP_C + scroll_offset;
	font_start = FONT_C + scroll_offset;
	max_chars = 48;
	if (width == 2) { /* standard width */
		char_start += 8;
		bitmap_start += 8;
		font_start += 8;
		max_chars = 40;
	}
	else if (width == 1) { /* narrow */
		char_start += 16;
		bitmap_start += 16;
		font_start += 16;
		max_chars = 32;
	}

	interval = (2 << md);
	max_chars = (max_chars >> md);
	for (i = 0; i <= 113; i++)
		antic_cycles[i] = '.';
	antic_cycles[114] = '\0';
	antic_cycles[0] = 'M';
	antic_cycles[1] = antic_cycles[6] = antic_cycles[7] = 'D';
	antic_cycles[2] = antic_cycles[3] = antic_cycles[4] = antic_cycles[5] = 'P';
	dram_pending = 0;
	for (i = 0; i <= 114; i++) {
		steal = 0;
		if (i <= END_C) {
			if (use_char_index && i >= char_start && ((i - char_start) % interval == 0)
				&& ((i - char_start) < max_chars * interval)) {
				steal = 'I';
			}
			if (use_font && i >= font_start && ((i - font_start) % interval == 0)
				&& ((i - font_start) < max_chars * interval)) {
				steal = 'F';
			}
			if (use_bitmap && i >= bitmap_start && ((i - bitmap_start) % interval == 0)
				&& ((i - bitmap_start) < max_chars * interval)) {
				steal = 'S';
			}
			if (i >= DMARS_C && i <= DMARE_C && ((i - DMARS_C) % 4 == 0)) {
				dram_pending = 1;
			}
		}
		if (steal !=0 ) {
			antic_cycles[i] = steal;
		}
		else if (dram_pending != 0){
			antic_cycles[i] = 'R';
			dram_pending = 0;
		}
	}
	cpu_cycle_map(antic_cycles, cpu_cycles, actual_cycles);
}