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
 unsigned int* crc32tab ; 

__attribute__((used)) static void init_crc32(void)
{
        /*
	 * the CRC-32 generator polynomial is:
	 *   x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^10
	 *        + x^8  + x^7  + x^5  + x^4  + x^2  + x + 1
	 */
        unsigned int crc32_polynomial = 0x04c11db7;
	unsigned int i,j;

	/*
	 * pre-calculate the CRC-32 remainder for each possible octet encoding
	 */
	for (i = 0;  i < 256;  i++) {
	        unsigned int crc_rem = i << 24;

		for (j = 0;  j < 8;  j++) {
		        if (crc_rem & 0x80000000)
			        crc_rem = (crc_rem << 1) ^ crc32_polynomial;
			else
			        crc_rem = (crc_rem << 1);
		}
		crc32tab[i] = crc_rem;
	}
}