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
 int w9966_findlen (int,int,int) ; 

__attribute__((used)) static int w9966_calcscale(int size, int min, int max, int* beg, int* end, unsigned char* factor)
{
	int maxlen = max - min;
	int len = *end - *beg + 1;
	int newlen = w9966_findlen(len, size, maxlen);
	int err = newlen - len;

	// Check for bad format
	if (newlen > maxlen || newlen < size)
		return -1;

	// Set factor (6 bit fixed)
	*factor = (64*size) / newlen;
	if (*factor == 64)
		*factor = 0x00;	// downscale is disabled
	else
		*factor |= 0x80; // set downscale-enable bit

	// Modify old beginning and end
	*beg -= err / 2;
	*end += err - (err / 2);

	// Move window if outside borders
	if (*beg < min) {
		*end += min - *beg;
		*beg += min - *beg;
	}
	if (*end > max) {
		*beg -= *end - max;
		*end -= *end - max;
	}

	return 0;
}