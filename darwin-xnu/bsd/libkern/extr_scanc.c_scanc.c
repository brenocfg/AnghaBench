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
typedef  size_t u_int ;
typedef  size_t u_char ;

/* Variables and functions */

int
scanc(u_int size, u_char *cp, const u_char table[], int mask0)
{
	u_char *end;
	u_char mask;

	mask = mask0;
	for (end = &cp[size]; cp != end && (table[*cp] & mask) == 0; ++cp);
	return (end - cp);
}