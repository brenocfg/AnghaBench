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
 int /*<<< orphan*/  TYPE_STRW ; 
 char* __nosan_strncat (char*,char const*,size_t) ; 
 int /*<<< orphan*/  kasan_check_range (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

char *
__asan_strncat(char *dst, const char *src, size_t sz)
{
	kasan_check_range(dst, strlen(dst) + sz + 1, TYPE_STRW);
	return __nosan_strncat(dst, src, sz);
}