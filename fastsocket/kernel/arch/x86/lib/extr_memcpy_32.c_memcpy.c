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
 void* __memcpy (void*,void const*,size_t) ; 
 void* __memcpy3d (void*,void const*,size_t) ; 

void *memcpy(void *to, const void *from, size_t n)
{
#ifdef CONFIG_X86_USE_3DNOW
	return __memcpy3d(to, from, n);
#else
	return __memcpy(to, from, n);
#endif
}