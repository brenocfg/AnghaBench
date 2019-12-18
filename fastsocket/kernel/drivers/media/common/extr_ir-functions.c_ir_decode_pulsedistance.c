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

int ir_decode_pulsedistance(u32 *samples, int count, int low, int high)
{
	int i,last,bit,len;
	u32 curBit;
	u32 value;

	/* find start burst */
	for (i = len = 0; i < count * 32; i++) {
		bit = getbit(samples,i);
		if (bit) {
			len++;
		} else {
			if (len >= 29)
				break;
			len = 0;
		}
	}

	/* start burst to short */
	if (len < 29)
		return 0xffffffff;

	/* find start silence */
	for (len = 0; i < count * 32; i++) {
		bit = getbit(samples,i);
		if (bit) {
			break;
		} else {
			len++;
		}
	}

	/* silence to short */
	if (len < 7)
		return 0xffffffff;

	/* go decoding */
	len   = 0;
	last = 1;
	value = 0; curBit = 1;
	for (; i < count * 32; i++) {
		bit  = getbit(samples,i);
		if (last) {
			if(bit) {
				continue;
			} else {
				len = 1;
			}
		} else {
			if (bit) {
				if (len > (low + high) /2)
					value |= curBit;
				curBit <<= 1;
				if (curBit == 1)
					break;
			} else {
				len++;
			}
		}
		last = bit;
	}

	return value;
}