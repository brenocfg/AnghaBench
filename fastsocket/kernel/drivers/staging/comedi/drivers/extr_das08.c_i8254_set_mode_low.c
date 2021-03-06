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
 scalar_t__ I8254_CTRL ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void i8254_set_mode_low(unsigned int base, int channel,
			       unsigned int mode)
{
	outb((channel << 6) | 0x30 | (mode & 0x0F), base + I8254_CTRL);
}