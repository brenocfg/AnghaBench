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
typedef  int u_int8_t ;
typedef  int u_int16_t ;

/* Variables and functions */
 int* __CFUniCharDecomposableBitmap ; 

int
unicode_decomposeable(u_int16_t character) {
	const u_int8_t *bitmap = __CFUniCharDecomposableBitmap;
	u_int8_t value;
	
	if (character < 0x00C0)
		return (0);

	value = bitmap[(character >> 8) & 0xFF];

	if (value == 0xFF) {
		return (1);
	} else if (value) {
		bitmap = bitmap + ((value - 1) * 32) + 256;
		return (bitmap[(character & 0xFF) / 8] & (1 << (character % 8)) ? 1 : 0);
	}
    	return (0);
}