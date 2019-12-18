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
typedef  int byte ;

/* Variables and functions */
 int* numBits ; 

byte MuLawEncode(short s) {
	unsigned long adjusted;
	byte sign, exponent, mantissa;

	sign = (s<0)?0:0x80;

	if (s<0) s=-s;
	adjusted = (long)s << (16-sizeof(short)*8);
	adjusted += 128L + 4L;
	if (adjusted > 32767) adjusted = 32767;
	exponent = numBits[(adjusted>>7)&0xff] - 1;
	mantissa = (adjusted>>(exponent+3))&0xf;
	return ~(sign | (exponent<<4) | mantissa);
}