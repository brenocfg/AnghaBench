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
 int /*<<< orphan*/  TYPE_MEMR ; 
 int /*<<< orphan*/  TYPE_MEMW ; 
 int /*<<< orphan*/  __nosan_bcopy (void const*,void*,size_t) ; 
 int /*<<< orphan*/  kasan_check_range (void*,size_t,int /*<<< orphan*/ ) ; 

void
__asan_bcopy(const void *src, void *dst, size_t sz)
{
	kasan_check_range(src, sz, TYPE_MEMR);
	kasan_check_range(dst, sz, TYPE_MEMW);
	__nosan_bcopy(src, dst, sz);
}