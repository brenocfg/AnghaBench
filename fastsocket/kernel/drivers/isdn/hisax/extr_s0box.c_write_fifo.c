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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  outb_p (int,unsigned int) ; 

__attribute__((used)) static inline void
write_fifo(unsigned int padr, signed int adr, u_char * data, int size)
{
	int i;
	outb_p(0x1c, padr+2);
	outb_p(0x14, padr+2);
	outb_p(adr&0x7f, padr);
	for (i=0; i<size; i++) {
		outb_p(0x16, padr+2);
		outb_p(*(data++), padr);
		outb_p(0x17, padr+2);
	}
	outb_p(0x14,padr+2);
	outb_p(0x1c,padr+2);
	return;
}