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
 int* memtimex_old ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void unset_ram_timings_(void)
{
	memregs[0x3802>>1] = memtimex_old[0];
	memregs[0x3804>>1] = memtimex_old[1] | 0x8000;
	printf("RAM timings reset to startup values.\n");
}