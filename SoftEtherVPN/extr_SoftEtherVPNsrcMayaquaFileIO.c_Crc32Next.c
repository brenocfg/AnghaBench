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
typedef  int UCHAR ;

/* Variables and functions */
 int* crc32_table ; 

UINT Crc32Next(void *buf, UINT pos, UINT len, UINT last_crc32)
{
	UINT ret = last_crc32;
	UINT i;

	for (i = 0;i < len;i++)
	{
		ret = (ret >> 8) ^ crc32_table[((UCHAR *)buf)[pos + i] ^ (ret & 0xff)];
	}

	return ret;
}