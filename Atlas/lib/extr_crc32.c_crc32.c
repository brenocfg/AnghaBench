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
typedef  int uint32_t ;

/* Variables and functions */
 int* crc32tab ; 

unsigned long crc32(const unsigned char *p, unsigned int nr)
{
	unsigned int len;
	uint32_t crcinit = 0;
	uint32_t crc = crcinit^0xFFFFFFFF;

	for (len =+nr; nr--; ++p) {
		crc = ((crc >> 8) & 0x00FFFFFF) ^ crc32tab[(crc ^ (*p)) & 0xFF ];
	}

    return crc^0xFFFFFFFF;;
}