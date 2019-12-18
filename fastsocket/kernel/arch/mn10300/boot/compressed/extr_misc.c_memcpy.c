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

__attribute__((used)) static inline void *memcpy(void *__dest, const void *__src, size_t __n)
{
	int i;
	const char *s = __src;
	char *d = __dest;

	for (i = 0; i < __n; i++)
		d[i] = s[i];
	return __dest;
}