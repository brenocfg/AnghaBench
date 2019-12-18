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
typedef  int u32 ;

/* Variables and functions */
 int getbit (int*,int) ; 

int ir_decode_biphase(u32 *samples, int count, int low, int high)
{
	int i,last,bit,len,flips;
	u32 value;

	/* find start bit (1) */
	for (i = 0; i < 32; i++) {
		bit = getbit(samples,i);
		if (bit)
			break;
	}

	/* go decoding */
	len   = 0;
	flips = 0;
	value = 1;
	for (; i < count * 32; i++) {
		if (len > high)
			break;
		if (flips > 1)
			break;
		last = bit;
		bit  = getbit(samples,i);
		if (last == bit) {
			len++;
			continue;
		}
		if (len < low) {
			len++;
			flips++;
			continue;
		}
		value <<= 1;
		value |= bit;
		flips = 0;
		len   = 1;
	}
	return value;
}