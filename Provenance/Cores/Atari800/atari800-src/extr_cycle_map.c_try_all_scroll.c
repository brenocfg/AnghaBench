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
 size_t CYCLE_MAP_SIZE ; 
 int /*<<< orphan*/  antic_steal_map (int,int,int,int,int,int,char*,int*,int*) ; 

__attribute__((used)) static void try_all_scroll(int md, int use_char_index,
	int use_font, int use_bitmap, int *cpu2antic, int *antic2cpu)
{
	char antic_cycles[115];
	int width;
	int scroll_offset = 0;
	width = 1; /* narrow width without scroll*/
	antic_steal_map(width, md, scroll_offset, use_char_index, use_font,
		use_bitmap, antic_cycles, &cpu2antic[CYCLE_MAP_SIZE * 0], &antic2cpu[CYCLE_MAP_SIZE * 0]);
	width = 2; /* standard without scroll or narrow with scroll */
	for (scroll_offset = 0; scroll_offset <= 7; scroll_offset++) {
		antic_steal_map(width, md, scroll_offset, use_char_index, use_font,
			use_bitmap, antic_cycles, &cpu2antic[CYCLE_MAP_SIZE * (1 + scroll_offset)],
			&antic2cpu[CYCLE_MAP_SIZE * (1 + scroll_offset)]);
	}
	width = 3; /* standard with scroll or wide */
	for (scroll_offset = 0; scroll_offset <= 7; scroll_offset++) {
		antic_steal_map(width, md, scroll_offset, use_char_index, use_font,
			use_bitmap, antic_cycles, &cpu2antic[CYCLE_MAP_SIZE * (9 + scroll_offset)],
			&antic2cpu[CYCLE_MAP_SIZE * (9 + scroll_offset)]);
	}
}