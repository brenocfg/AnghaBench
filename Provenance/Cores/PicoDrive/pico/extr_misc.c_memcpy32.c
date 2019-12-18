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
typedef  int /*<<< orphan*/  intblock ;

/* Variables and functions */

void memcpy32(int *dest, int *src, int count)
{
	intblock *bd = (intblock *) dest, *bs = (intblock *) src;

	for (; count >= sizeof(*bd)/4; count -= sizeof(*bd)/4)
		*bd++ = *bs++;

	dest = (int *)bd; src = (int *)bs;
	while (count--)
		*dest++ = *src++;
}