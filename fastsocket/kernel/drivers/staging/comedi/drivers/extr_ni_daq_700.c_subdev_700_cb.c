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
 scalar_t__ DIO_R ; 
 scalar_t__ DIO_W ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int subdev_700_cb(int dir, int port, int data, unsigned long arg)
{
	/* port is always A for output and B for input (8255 emu) */
	unsigned long iobase = arg;

	if (dir) {
		outb(data, iobase + DIO_W);
		return 0;
	} else {
		return inb(iobase + DIO_R);
	}
}