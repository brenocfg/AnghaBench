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

__attribute__((used)) static __inline void fast_write(unsigned int f, void *dst, unsigned int bytes)
{
#ifndef X86X64
	unsigned char *p = (unsigned char*)dst;

	switch (bytes)
	{
		case 4: 
			*p = (unsigned char)f;
			*(p + 1) = (unsigned char)(f >> 8);
			*(p + 2) = (unsigned char)(f >> 16);
			*(p + 3) = (unsigned char)(f >> 24);
			return;
		case 3:
			*p = (unsigned char)f;
			*(p + 1) = (unsigned char)(f >> 8);
			*(p + 2) = (unsigned char)(f >> 16);
			return;
		case 2:
			*p = (unsigned char)f;
			*(p + 1) = (unsigned char)(f >> 8);
			return;
		case 1:
			*p = (unsigned char)f;
			return;
	}
#else
	switch (bytes)
	{
		case 4: 
			*((unsigned int*)dst) = f;
			return;
		case 3:
			*((unsigned int*)dst) = f;
			return;
		case 2:
#if QLZ_COMPRESSION_LEVEL == 0
// 2 byte writes are common in level 0
			*((unsigned short int*)dst) = (unsigned short int)f;
#else
			*((unsigned int*)dst) = f;
#endif
			return;
		case 1:
			*((unsigned char*)dst) = (unsigned char)f;
			return;
	}
#endif
}