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
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nes_debug (unsigned int,char*,...) ; 
 unsigned int nes_debug_level ; 

void nes_dump_mem(unsigned int dump_debug_level, void *addr, int length)
{
	char  xlate[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'a', 'b', 'c', 'd', 'e', 'f'};
	char  *ptr;
	char  hex_buf[80];
	char  ascii_buf[20];
	int   num_char;
	int   num_ascii;
	int   num_hex;

	if (!(nes_debug_level & dump_debug_level)) {
		return;
	}

	ptr = addr;
	if (length > 0x100) {
		nes_debug(dump_debug_level, "Length truncated from %x to %x\n", length, 0x100);
		length = 0x100;
	}
	nes_debug(dump_debug_level, "Address=0x%p, length=0x%x (%d)\n", ptr, length, length);

	memset(ascii_buf, 0, 20);
	memset(hex_buf, 0, 80);

	num_ascii = 0;
	num_hex = 0;
	for (num_char = 0; num_char < length; num_char++) {
		if (num_ascii == 8) {
			ascii_buf[num_ascii++] = ' ';
			hex_buf[num_hex++] = '-';
			hex_buf[num_hex++] = ' ';
		}

		if (*ptr < 0x20 || *ptr > 0x7e)
			ascii_buf[num_ascii++] = '.';
		else
			ascii_buf[num_ascii++] = *ptr;
		hex_buf[num_hex++] = xlate[((*ptr & 0xf0) >> 4)];
		hex_buf[num_hex++] = xlate[*ptr & 0x0f];
		hex_buf[num_hex++] = ' ';
		ptr++;

		if (num_ascii >= 17) {
			/* output line and reset */
			nes_debug(dump_debug_level, "   %s |  %s\n", hex_buf, ascii_buf);
			memset(ascii_buf, 0, 20);
			memset(hex_buf, 0, 80);
			num_ascii = 0;
			num_hex = 0;
		}
	}

	/* output the rest */
	if (num_ascii) {
		while (num_ascii < 17) {
			if (num_ascii == 8) {
				hex_buf[num_hex++] = ' ';
				hex_buf[num_hex++] = ' ';
			}
			hex_buf[num_hex++] = ' ';
			hex_buf[num_hex++] = ' ';
			hex_buf[num_hex++] = ' ';
			num_ascii++;
		}

		nes_debug(dump_debug_level, "   %s |  %s\n", hex_buf, ascii_buf);
	}
}