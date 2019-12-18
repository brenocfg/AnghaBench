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
 int /*<<< orphan*/  sh7751systemh_inw (unsigned long) ; 

void sh7751systemh_insw(unsigned long port, void *addr, unsigned long count)
{
	unsigned short *p = addr;
	while (count--) *p++ = sh7751systemh_inw(port);
}