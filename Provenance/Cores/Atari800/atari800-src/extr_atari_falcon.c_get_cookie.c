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
 scalar_t__ Setexc (int,long) ; 

int get_cookie(long cookie, long *value)
{
	long *cookiejar = (long *) Setexc(0x168, -1L);

	if (cookiejar) {
		while (*cookiejar) {
			if (*cookiejar == cookie) {
				if (value)
					*value = *++cookiejar;
				return (1);
			}
			cookiejar += 2;
		}
	}
	return (0);
}