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
 unsigned int inb (unsigned int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static unsigned int i8254_read_status_low(unsigned int base, int channel)
{
	outb(0xE0 | (2 << channel), base + I8254_CTRL);
	return inb(base + channel);
}