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

__attribute__((used)) static long rnc_crc (void *data, long len) {
    unsigned short crctab[256];
    unsigned short val;
    int i, j;
    unsigned char *p = data;

    for (i=0; i<256; i++) {
	val = i;

	for (j=0; j<8; j++) {
	    if (val & 1)
		val = (val >> 1) ^ 0xA001;
	    else
		val = (val >> 1);
	}
	crctab[i] = val;
    }

    val = 0;
    while (len--) {
	val ^= *p++;
	val = (val >> 8) ^ crctab[val & 0xFF];
    }

    return val;
}