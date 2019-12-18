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
 int /*<<< orphan*/  sh7751systemh_outw (int /*<<< orphan*/ ,unsigned long) ; 

void sh7751systemh_outsw(unsigned long port, const void *addr, unsigned long count)
{
	unsigned short *p = (unsigned short*)addr;
	while (count--) sh7751systemh_outw(*p++, port);
}