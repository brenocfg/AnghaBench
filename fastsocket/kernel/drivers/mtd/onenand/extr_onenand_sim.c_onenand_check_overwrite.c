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

__attribute__((used)) static int onenand_check_overwrite(void *dest, void *src, size_t count)
{
	unsigned int *s = (unsigned int *) src;
	unsigned int *d = (unsigned int *) dest;
	int i;

	count >>= 2;
	for (i = 0; i < count; i++)
		if ((*s++ ^ *d++) != 0)
			return 1;

	return 0;
}