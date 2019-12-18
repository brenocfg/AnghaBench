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

unsigned long
hash(const void *addr, int length)
{
		const unsigned char *k, *e;
		unsigned long h;
		
		k = (const unsigned char *)addr;
		e = k+length;
		for (h=0; k< e;++k)
		{
				h *=16777619;
				h ^= *k;
		}
		return (h);
}