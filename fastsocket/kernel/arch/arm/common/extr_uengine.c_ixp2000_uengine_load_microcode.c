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
typedef  scalar_t__ u8 ;
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  USTORE_ADDRESS ; 
 int ixp2000_uengine_csr_read (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixp2000_uengine_csr_write (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ustore_write (int,int) ; 

void ixp2000_uengine_load_microcode(int uengine, u8 *ucode, int insns)
{
	int i;

	/*
	 * Start writing to microstore at address 0.
	 */
	ixp2000_uengine_csr_write(uengine, USTORE_ADDRESS, 0x80000000);
	for (i = 0; i < insns; i++) {
		u64 insn;

		insn = (((u64)ucode[0]) << 32) |
			(((u64)ucode[1]) << 24) |
			(((u64)ucode[2]) << 16) |
			(((u64)ucode[3]) << 8) |
			((u64)ucode[4]);
		ucode += 5;

		ustore_write(uengine, insn);
	}

	/*
 	 * Pad with a few NOPs at the end (to avoid the microengine
	 * aborting as it prefetches beyond the last instruction), unless
	 * we run off the end of the instruction store first, at which
	 * point the address register will wrap back to zero.
	 */
	for (i = 0; i < 4; i++) {
		u32 addr;

		addr = ixp2000_uengine_csr_read(uengine, USTORE_ADDRESS);
		if (addr == 0x80000000)
			break;
		ustore_write(uengine, 0xf0000c0300ULL);
	}

	/*
	 * End programming.
	 */
	ixp2000_uengine_csr_write(uengine, USTORE_ADDRESS, 0x00000000);
}