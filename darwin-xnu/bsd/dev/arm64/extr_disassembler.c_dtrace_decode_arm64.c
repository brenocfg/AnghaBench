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
typedef  int uint32_t ;
struct TYPE_2__ {int mask; int value; int type; } ;

/* Variables and functions */
 int FASTTRAP_T_COMMON ; 
 unsigned int NUM_DECODE_ENTRIES ; 
 TYPE_1__* arm64_decode_table ; 

int dtrace_decode_arm64(uint32_t instr)
{
	unsigned i;

	for (i = 0; i < NUM_DECODE_ENTRIES; i++) {
		if ((instr & arm64_decode_table[i].mask) == arm64_decode_table[i].value) {
			return arm64_decode_table[i].type;
		}
	}

	return FASTTRAP_T_COMMON;
}