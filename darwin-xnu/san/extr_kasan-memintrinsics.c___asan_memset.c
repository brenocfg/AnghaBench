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
 int /*<<< orphan*/  TYPE_MEMW ; 
 void* __nosan_memset (void*,int,size_t) ; 
 int /*<<< orphan*/  kasan_check_range (void*,size_t,int /*<<< orphan*/ ) ; 

void *
__asan_memset(void *dst, int c, size_t sz)
{
	kasan_check_range(dst, sz, TYPE_MEMW);
	return __nosan_memset(dst, c, sz);
}