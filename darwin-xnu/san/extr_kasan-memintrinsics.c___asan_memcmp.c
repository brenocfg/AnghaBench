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
 int __nosan_memcmp (void const*,void const*,size_t) ; 
 int /*<<< orphan*/  kasan_check_range (void const*,size_t,int /*<<< orphan*/ ) ; 

int
__asan_memcmp(const void *a, const void *b, size_t n)
{
	kasan_check_range(a, n, TYPE_MEMR);
	kasan_check_range(b, n, TYPE_MEMR);
	return __nosan_memcmp(a, b, n);
}