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
 int /*<<< orphan*/  delay () ; 
 int /*<<< orphan*/  microdev_outb (unsigned char,unsigned long) ; 

void microdev_outb_p(unsigned char b, unsigned long port)
{
	microdev_outb(b, port);
	delay();
}