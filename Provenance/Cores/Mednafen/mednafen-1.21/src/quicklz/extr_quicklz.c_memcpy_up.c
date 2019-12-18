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
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,unsigned int) ; 

__attribute__((used)) static __inline void memcpy_up(unsigned char *dst, const unsigned char *src, unsigned int n)
{
	// cannot be replaced by overlap handling of memmove() due to LZSS algorithm
#ifndef X86X64

	if(n > 8 && src + n < dst)
		memcpy(dst, src, n);
	else
	{
		unsigned char *end = dst + n;
		while(dst < end)
		{
			*dst = *src;
			dst++;
			src++;
		}
	}
#else
	if (n < 5)
		*((unsigned int*)dst) = *((unsigned int*)src);
	else
	{
		unsigned char *end = dst + n;
		while(dst < end)
		{
			*((unsigned int*)dst) = *((unsigned int*)src);
			dst = dst + 4;
			src = src + 4;
		}
	}
#endif
}