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
 unsigned int EmulateCPDO (unsigned int) ; 
 unsigned int EmulateCPDT (unsigned int) ; 
 unsigned int EmulateCPRT (unsigned int) ; 
 int /*<<< orphan*/  printk (char*,unsigned int) ; 

unsigned int EmulateAll(unsigned int opcode)
{
	unsigned int code;

#ifdef NWFPE_DEBUG
	printk("NWFPE: emulating opcode %08x\n", opcode);
#endif
	code = opcode & 0x00000f00;
	if (code == 0x00000100 || code == 0x00000200) {
		/* For coprocessor 1 or 2 (FPA11) */
		code = opcode & 0x0e000000;
		if (code == 0x0e000000) {
			if (opcode & 0x00000010) {
				/* Emulate conversion opcodes. */
				/* Emulate register transfer opcodes. */
				/* Emulate comparison opcodes. */
				return EmulateCPRT(opcode);
			} else {
				/* Emulate monadic arithmetic opcodes. */
				/* Emulate dyadic arithmetic opcodes. */
				return EmulateCPDO(opcode);
			}
		} else if (code == 0x0c000000) {
			/* Emulate load/store opcodes. */
			/* Emulate load/store multiple opcodes. */
			return EmulateCPDT(opcode);
		}
	}

	/* Invalid instruction detected.  Return FALSE. */
	return 0;
}