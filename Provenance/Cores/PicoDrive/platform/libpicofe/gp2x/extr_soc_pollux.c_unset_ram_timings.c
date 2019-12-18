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
 int* memregs ; 
 int /*<<< orphan*/  printf (char*) ; 
 int* saved_memtimex ; 

__attribute__((used)) static void unset_ram_timings(void)
{
	int i;

	memregs[0x14802>>1] = saved_memtimex[0];
	memregs[0x14804>>1] = saved_memtimex[1] | 0x8000;

	for (i = 0; i < 0x100000; i++)
		if (!(memregs[0x14804>>1] & 0x8000))
			break;

	printf("RAM timings reset to startup values.\n");
}