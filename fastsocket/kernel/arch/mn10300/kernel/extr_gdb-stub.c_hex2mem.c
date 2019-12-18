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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ gdbstub_write_byte (int,int*) ; 
 scalar_t__ gdbstub_write_dword (int,int*) ; 
 scalar_t__ gdbstub_write_word (int,int*) ; 
 int hex (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
const char *hex2mem(const char *buf, void *_mem, int count, int may_fault)
{
	u8 *mem = _mem;
	union {
		u32 val;
		u8 b[4];
	} ch;

	if ((u32) mem & 1 && count >= 1) {
		ch.b[0]  = hex(*buf++) << 4;
		ch.b[0] |= hex(*buf++);
		if (gdbstub_write_byte(ch.val, mem) != 0)
			return 0;
		mem++;
		count--;
	}

	if ((u32) mem & 3 && count >= 2) {
		ch.b[0]  = hex(*buf++) << 4;
		ch.b[0] |= hex(*buf++);
		ch.b[1]  = hex(*buf++) << 4;
		ch.b[1] |= hex(*buf++);
		if (gdbstub_write_word(ch.val, mem) != 0)
			return 0;
		mem += 2;
		count -= 2;
	}

	while (count >= 4) {
		ch.b[0]  = hex(*buf++) << 4;
		ch.b[0] |= hex(*buf++);
		ch.b[1]  = hex(*buf++) << 4;
		ch.b[1] |= hex(*buf++);
		ch.b[2]  = hex(*buf++) << 4;
		ch.b[2] |= hex(*buf++);
		ch.b[3]  = hex(*buf++) << 4;
		ch.b[3] |= hex(*buf++);
		if (gdbstub_write_dword(ch.val, mem) != 0)
			return 0;
		mem += 4;
		count -= 4;
	}

	if (count >= 2) {
		ch.b[0]  = hex(*buf++) << 4;
		ch.b[0] |= hex(*buf++);
		ch.b[1]  = hex(*buf++) << 4;
		ch.b[1] |= hex(*buf++);
		if (gdbstub_write_word(ch.val, mem) != 0)
			return 0;
		mem += 2;
		count -= 2;
	}

	if (count >= 1) {
		ch.b[0]  = hex(*buf++) << 4;
		ch.b[0] |= hex(*buf++);
		if (gdbstub_write_byte(ch.val, mem) != 0)
			return 0;
	}

	return buf;
}