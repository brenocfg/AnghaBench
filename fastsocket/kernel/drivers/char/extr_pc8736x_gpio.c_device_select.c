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
 int /*<<< orphan*/  SIO_UNIT_SEL ; 
 unsigned int selected_device ; 
 int /*<<< orphan*/  superio_outb (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void device_select(unsigned devldn)
{
	superio_outb(SIO_UNIT_SEL, devldn);
	selected_device = devldn;
}