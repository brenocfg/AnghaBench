#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int s0_3; unsigned int s3_3; scalar_t__ s2_3; scalar_t__ s1_3; } ;

/* Variables and functions */
 size_t E04 ; 
 char** error_message ; 
 int /*<<< orphan*/  gdb_cris_strcpy (scalar_t__*,char*) ; 
 scalar_t__* output_buffer ; 
 TYPE_1__ sreg ; 

__attribute__((used)) static void remove_watchpoint(char type, int addr, int len)
{
	/* Breakpoint/watchpoint types:
	   0 = memory breakpoint for instructions
	   (not supported; done via memory write instead)
	   1 = hardware breakpoint for instructions (supported)
	   2 = write watchpoint (supported)
	   3 = read watchpoint (supported)
	   4 = access watchpoint (supported) */
	if (type < '1' || type > '4') {
		output_buffer[0] = 0;
		return;
	}

	/* Read watchpoints are set as access watchpoints, because of GDB's
	   inability to deal with pure read watchpoints. */
	if (type == '3')
		type = '4';

	if (type == '1') {
		/* Hardware breakpoint. */
		/* Bit 0 in BP_CTRL holds the configuration for I0. */
		if (!(sreg.s0_3 & 0x1)) {
			/* Not in use. */
			gdb_cris_strcpy(output_buffer, error_message[E04]);
			return;
		}
		/* Deconfigure. */
		sreg.s1_3 = 0;
		sreg.s2_3 = 0;
		sreg.s0_3 &= ~1;
	} else {
		int bp;
		unsigned int *bp_d_regs = &sreg.s3_3;
		/* Try to find a watchpoint that is configured for the
		   specified range, then check that read/write also matches. */

		/* Ugly pointer arithmetic, since I cannot rely on a
		   single switch (addr) as there may be several watchpoints with
		   the same start address for example. */

		for (bp = 0; bp < 6; bp++) {
			if (bp_d_regs[bp * 2] == addr &&
			    bp_d_regs[bp * 2 + 1] == (addr + len - 1)) {
				/* Matching range. */
				int bitpos = 2 + bp * 4;
				int rw_bits;

				/* Read/write bits for this BP. */
				rw_bits = (sreg.s0_3 & (0x3 << bitpos)) >> bitpos;

				if ((type == '3' && rw_bits == 0x1) ||
				    (type == '2' && rw_bits == 0x2) ||
				    (type == '4' && rw_bits == 0x3)) {
					/* Read/write matched. */
					break;
				}
			}
		}

		if (bp > 5) {
			/* No watchpoint matched. */
			gdb_cris_strcpy(output_buffer, error_message[E04]);
			return;
		}

		/* Found a matching watchpoint. Now, deconfigure it by
		   both disabling read/write in bp_ctrl and zeroing its
		   start/end addresses. */
		sreg.s0_3 &= ~(3 << (2 + (bp * 4)));
		bp_d_regs[bp * 2] = 0;
		bp_d_regs[bp * 2 + 1] = 0;
	}

	/* Note that we don't clear the S1 flag here. It's done when continuing.  */
	gdb_cris_strcpy(output_buffer, "OK");
}