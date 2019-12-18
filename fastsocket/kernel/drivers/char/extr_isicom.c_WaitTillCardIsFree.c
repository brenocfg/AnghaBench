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
 unsigned int in_atomic () ; 
 int inw (unsigned long) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static inline int WaitTillCardIsFree(unsigned long base)
{
	unsigned int count = 0;
	unsigned int a = in_atomic(); /* do we run under spinlock? */

	while (!(inw(base + 0xe) & 0x1) && count++ < 100)
		if (a)
			mdelay(1);
		else
			msleep(1);

	return !(inw(base + 0xe) & 0x1);
}