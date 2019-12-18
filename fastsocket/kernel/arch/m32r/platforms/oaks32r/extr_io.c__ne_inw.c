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
typedef  scalar_t__ portp ;

/* Variables and functions */

__attribute__((used)) static inline unsigned short _ne_inw(void *portp)
{
	unsigned short tmp;

	tmp = *(unsigned short *)(portp) & 0xff;
	tmp |= *(unsigned short *)(portp+2) << 8;
	return tmp;
}