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
struct sm501fb_info {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void sm501fb_setup_gamma(struct sm501fb_info *fbi,
				unsigned long palette)
{
	unsigned long value = 0;
	int offset;

	/* set gamma values */
	for (offset = 0; offset < 256 * 4; offset += 4) {
		writel(value, fbi->regs + palette + offset);
		value += 0x010101; 	/* Advance RGB by 1,1,1.*/
	}
}