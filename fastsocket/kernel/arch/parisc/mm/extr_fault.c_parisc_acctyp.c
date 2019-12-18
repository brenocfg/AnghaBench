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
 int /*<<< orphan*/  BITSSET ; 
 unsigned long VM_EXEC ; 
 unsigned long VM_READ ; 
 unsigned long VM_WRITE ; 
 int /*<<< orphan*/  bit22set (unsigned int) ; 
 int /*<<< orphan*/  bits23_25set (unsigned int) ; 
 int /*<<< orphan*/  isGraphicsFlushRead (unsigned int) ; 

__attribute__((used)) static unsigned long
parisc_acctyp(unsigned long code, unsigned int inst)
{
	if (code == 6 || code == 16)
	    return VM_EXEC;

	switch (inst & 0xf0000000) {
	case 0x40000000: /* load */
	case 0x50000000: /* new load */
		return VM_READ;

	case 0x60000000: /* store */
	case 0x70000000: /* new store */
		return VM_WRITE;

	case 0x20000000: /* coproc */
	case 0x30000000: /* coproc2 */
		if (bit22set(inst))
			return VM_WRITE;

	case 0x0: /* indexed/memory management */
		if (bit22set(inst)) {
			/*
			 * Check for the 'Graphics Flush Read' instruction.
			 * It resembles an FDC instruction, except for bits
			 * 20 and 21. Any combination other than zero will
			 * utilize the block mover functionality on some
			 * older PA-RISC platforms.  The case where a block
			 * move is performed from VM to graphics IO space
			 * should be treated as a READ.
			 *
			 * The significance of bits 20,21 in the FDC
			 * instruction is:
			 *
			 *   00  Flush data cache (normal instruction behavior)
			 *   01  Graphics flush write  (IO space -> VM)
			 *   10  Graphics flush read   (VM -> IO space)
			 *   11  Graphics flush read/write (VM <-> IO space)
			 */
			if (isGraphicsFlushRead(inst))
				return VM_READ;
			return VM_WRITE;
		} else {
			/*
			 * Check for LDCWX and LDCWS (semaphore instructions).
			 * If bits 23 through 25 are all 1's it is one of
			 * the above two instructions and is a write.
			 *
			 * Note: With the limited bits we are looking at,
			 * this will also catch PROBEW and PROBEWI. However,
			 * these should never get in here because they don't
			 * generate exceptions of the type:
			 *   Data TLB miss fault/data page fault
			 *   Data memory protection trap
			 */
			if (bits23_25set(inst) == BITSSET)
				return VM_WRITE;
		}
		return VM_READ; /* Default */
	}
	return VM_READ; /* Default */
}