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
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * twirl ; 

void platform_heartbeat(void)
{
#if 0
	static int i = 0, j = 0;

	if (--i < 0) {
		i = 99;
		printk("\r%c\r", twirl[j++]);
		if (j == 8)
			j = 0;
	}
#endif
}