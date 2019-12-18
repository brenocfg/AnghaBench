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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  gdbstub_read_byte (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdbstub_read_dword (int /*<<< orphan*/  const*,int*) ; 
 int /*<<< orphan*/  gdbstub_read_word (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 char* pack_hex_byte (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char *mem2hex(const void *_mem, char *buf, int count, int may_fault)
{
	const uint8_t *mem = _mem;
	uint8_t ch[4] __attribute__((aligned(4)));

	if ((uint32_t)mem&1 && count>=1) {
		if (!gdbstub_read_byte(mem,ch))
			return NULL;
		buf = pack_hex_byte(buf, ch[0]);
		mem++;
		count--;
	}

	if ((uint32_t)mem&3 && count>=2) {
		if (!gdbstub_read_word(mem,(uint16_t *)ch))
			return NULL;
		buf = pack_hex_byte(buf, ch[0]);
		buf = pack_hex_byte(buf, ch[1]);
		mem += 2;
		count -= 2;
	}

	while (count>=4) {
		if (!gdbstub_read_dword(mem,(uint32_t *)ch))
			return NULL;
		buf = pack_hex_byte(buf, ch[0]);
		buf = pack_hex_byte(buf, ch[1]);
		buf = pack_hex_byte(buf, ch[2]);
		buf = pack_hex_byte(buf, ch[3]);
		mem += 4;
		count -= 4;
	}

	if (count>=2) {
		if (!gdbstub_read_word(mem,(uint16_t *)ch))
			return NULL;
		buf = pack_hex_byte(buf, ch[0]);
		buf = pack_hex_byte(buf, ch[1]);
		mem += 2;
		count -= 2;
	}

	if (count>=1) {
		if (!gdbstub_read_byte(mem,ch))
			return NULL;
		buf = pack_hex_byte(buf, ch[0]);
	}

	*buf = 0;

	return buf;
}