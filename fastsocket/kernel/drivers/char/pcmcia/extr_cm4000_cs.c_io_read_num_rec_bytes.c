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
 int /*<<< orphan*/  REG_FLAGS0 (unsigned int) ; 
 int /*<<< orphan*/  REG_NUM_BYTES (unsigned int) ; 
 int inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned short io_read_num_rec_bytes(unsigned int iobase,
					    unsigned short *s)
{
	unsigned short tmp;

	tmp = *s = 0;
	do {
		*s = tmp;
		tmp = inb(REG_NUM_BYTES(iobase)) |
				(inb(REG_FLAGS0(iobase)) & 4 ? 0x100 : 0);
	} while (tmp != *s);

	return *s;
}