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
typedef  long u32 ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 long* slic_crc_table ; 

__attribute__((used)) static void slic_mcast_init_crc32(void)
{
	u32 c;		/*  CRC shit reg                 */
	u32 e = 0;		/*  Poly X-or pattern            */
	int i;			/*  counter                      */
	int k;			/*  byte being shifted into crc  */

	static int p[] = { 0, 1, 2, 4, 5, 7, 8, 10, 11, 12, 16, 22, 23, 26 };

	for (i = 0; i < ARRAY_SIZE(p); i++)
		e |= 1L << (31 - p[i]);

	for (i = 1; i < 256; i++) {
		c = i;
		for (k = 8; k; k--)
			c = c & 1 ? (c >> 1) ^ e : c >> 1;
		slic_crc_table[i] = c;
	}
}