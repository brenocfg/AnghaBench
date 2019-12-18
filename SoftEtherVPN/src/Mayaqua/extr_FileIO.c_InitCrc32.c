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
typedef  int UINT ;

/* Variables and functions */
 int* crc32_table ; 

void InitCrc32()
{
	UINT poly = 0xEDB88320;
	UINT u, i, j;

	for (i = 0;i < 256;i++)
	{
		u = i;

		for (j = 0;j < 8;j++)
		{
			if ((u & 0x1) != 0)
			{
				u = (u >> 1) ^ poly;
			}
			else
			{
				u >>= 1;
			}
		}

		crc32_table[i] = u;
	}
}