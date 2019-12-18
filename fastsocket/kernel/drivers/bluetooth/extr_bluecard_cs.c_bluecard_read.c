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
typedef  void* __u8 ;

/* Variables and functions */
 scalar_t__ REG_COMMAND ; 
 int /*<<< orphan*/  REG_COMMAND_RX_WIN_ONE ; 
 int /*<<< orphan*/  REG_COMMAND_RX_WIN_TWO ; 
 void* inb (unsigned int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int bluecard_read(unsigned int iobase, unsigned int offset, __u8 *buf, int size)
{
	int i, n, len;

	outb(REG_COMMAND_RX_WIN_ONE, iobase + REG_COMMAND);

	len = inb(iobase + offset);
	n = 0;
	i = 1;

	while (n < len) {

		if (i == 16) {
			outb(REG_COMMAND_RX_WIN_TWO, iobase + REG_COMMAND);
			i = 0;
		}

		buf[n] = inb(iobase + offset + i);

		n++;
		i++;

	}

	return len;
}