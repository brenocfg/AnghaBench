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
 int /*<<< orphan*/  GP1_IO_BASE ; 
 int /*<<< orphan*/  GP2_IO_BASE ; 
 int inb (int /*<<< orphan*/ ) ; 

unsigned int nw_gpio_read(void)
{
	return inb(GP1_IO_BASE) | inb(GP2_IO_BASE) << 8;
}