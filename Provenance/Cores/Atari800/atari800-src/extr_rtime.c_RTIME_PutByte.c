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
typedef  int UBYTE ;

/* Variables and functions */
 int* regset ; 
 int rtime_state ; 
 size_t rtime_tmp ; 
 int rtime_tmp2 ; 

void RTIME_PutByte(UBYTE byte)
{
	switch (rtime_state) {
	case 0:
		rtime_tmp = byte & 0x0f;
		rtime_state = 1;
		break;
	case 1:
		rtime_tmp2 = byte << 4;
		rtime_state = 2;
		break;
	case 2:
		regset[rtime_tmp] = rtime_tmp2 | (byte & 0x0f);
		rtime_state = 0;
		break;
	}
}