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
typedef  int /*<<< orphan*/  mask ;

/* Variables and functions */
 int __builtin_clz (unsigned int) ; 

int
fls(unsigned int mask)
{
	if (mask == 0)
		return 0;

	return (sizeof (mask) << 3) - __builtin_clz(mask);
}