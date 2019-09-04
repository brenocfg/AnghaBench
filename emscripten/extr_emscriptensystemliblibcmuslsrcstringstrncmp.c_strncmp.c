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

int strncmp(const char *_l, const char *_r, size_t n)
{
	const unsigned char *l=(void *)_l, *r=(void *)_r;
	if (!n--) return 0;
	for (; *l && *r && n && *l == *r ; l++, r++, n--);
	return *l - *r;
}