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

__attribute__((used)) static void crc8_byte(unsigned int *crc, unsigned char db)
{
	int i,f;

	for(i=0;i<8;i++) {
		f = (*crc ^ db) & 1;
		*crc >>= 1;
		db >>= 1;
		if(f)
			*crc ^= 0x8c;
	}
	*crc &= 0xff;
}