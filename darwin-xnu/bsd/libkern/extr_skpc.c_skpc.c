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
typedef  int u_char ;

/* Variables and functions */

int
skpc(int mask0, int size, char *cp0)
{
	u_char *cp, *end, mask;

	mask = mask0;
	cp = (u_char *)cp0;
	for (end = &cp[size]; cp < end && *cp == mask; ++cp);
	return (end - cp);
}