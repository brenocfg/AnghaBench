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
 int CYCLE_MAP_SIZE ; 
 int* CYCLE_MAP_antic2cpu ; 
 int* CYCLE_MAP_cpu2antic ; 
 int /*<<< orphan*/  antic_steal_map (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  try_all_scroll (int,int,int,int,int*,int*) ; 

void CYCLE_MAP_Create(void)
{
#ifdef TEST_CYCLE_MAP
	int i, j;
	int *cpu_cycles;
	int *actual_cycles;
#endif
	char antic_cycles[115];
	int k = 0;
	antic_steal_map(1, 0, 0, 0, 0, 0, antic_cycles, &CYCLE_MAP_cpu2antic[k], &CYCLE_MAP_antic2cpu[k]); /* blank line, or mode 8-F following line*/
	k = CYCLE_MAP_SIZE * (17 * 0 + 1);
	try_all_scroll(0, 1, 1, 0, &CYCLE_MAP_cpu2antic[k], &CYCLE_MAP_antic2cpu[k]); /* mode 2,3,4,5 first line */
	k = CYCLE_MAP_SIZE * (17 * 1 + 1);
	try_all_scroll(0, 0, 1, 0, &CYCLE_MAP_cpu2antic[k], &CYCLE_MAP_antic2cpu[k]); /* mode 2,3,4,5 following lines */
	k = CYCLE_MAP_SIZE * (17 * 2 + 1);
	try_all_scroll(1, 1, 1, 0, &CYCLE_MAP_cpu2antic[k], &CYCLE_MAP_antic2cpu[k]); /* mode 6,7 first line */
	k = CYCLE_MAP_SIZE * (17 * 3 + 1);
	try_all_scroll(1, 0, 1, 0, &CYCLE_MAP_cpu2antic[k], &CYCLE_MAP_antic2cpu[k]); /* mode 6,7 following lines */
	k = CYCLE_MAP_SIZE * (17 * 4 + 1);
	try_all_scroll(0, 0, 0, 1, &CYCLE_MAP_cpu2antic[k], &CYCLE_MAP_antic2cpu[k]); /* mode 8,9 first line */
	k = CYCLE_MAP_SIZE * (17 * 5 + 1);
	try_all_scroll(1, 0, 0, 1, &CYCLE_MAP_cpu2antic[k], &CYCLE_MAP_antic2cpu[k]); /* mode A,B,C  first line */
	k = CYCLE_MAP_SIZE * (17 * 6 + 1);
	try_all_scroll(2, 0, 0, 1, &CYCLE_MAP_cpu2antic[k], &CYCLE_MAP_antic2cpu[k]); /* mode D,E,F  first line */
#ifdef TEST_CYCLE_MAP
	for(j = 0; j < 17 * 7 + 1; j++) {
		cpu_cycles = &CYCLE_MAP_cpu2antic[CYCLE_MAP_SIZE * j];
		actual_cycles = &CYCLE_MAP_antic2cpu[CYCLE_MAP_SIZE * j];
		printf("%3d ", actual_cycles[114]);
		for(i = 0; i <= actual_cycles[114] + 6; i++)
			printf("%3d, ", cpu_cycles[i]);
		printf("\n");
	}
#endif
}