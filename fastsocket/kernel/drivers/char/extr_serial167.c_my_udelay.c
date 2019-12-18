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
typedef  int /*<<< orphan*/  volatile u_char ;

/* Variables and functions */

void my_udelay(long us)
{
	u_char x;
	volatile u_char *p = &x;
	int i;

	while (us--)
		for (i = 100; i; i--)
			x |= *p;
}