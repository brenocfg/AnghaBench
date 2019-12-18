#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ccs; } ;
struct TYPE_3__ {int s0_3; int s1_3; int s2_3; unsigned int s3_3; } ;

/* Variables and functions */
 int CCS_SHIFT ; 
 size_t E04 ; 
 int S_CCS_BITNR ; 
 char** error_message ; 
 int /*<<< orphan*/  gdb_cris_strcpy (scalar_t__*,char*) ; 
 scalar_t__* output_buffer ; 
 TYPE_2__ reg ; 
 TYPE_1__ sreg ; 

__attribute__((used)) static void insert_watchpoint(char type, int addr, int len)
{
	/* Breakpoint/watchpoint types (GDB terminology):
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
		/* Hardware (instruction) breakpoint. */
		/* Bit 0 in BP_CTRL holds the configuration for I0. */
		if (sreg.s0_3 & 0x1) {
			/* Already in use. */
			gdb_cris_strcpy(output_buffer, error_message[E04]);
			return;
		}
		/* Configure. */
		sreg.s1_3 = addr;
		sreg.s2_3 = (addr + len - 1);
		sreg.s0_3 |= 1;
	} else {
		int bp;
		unsigned int *bp_d_regs = &sreg.s3_3;

		/* The watchpoint allocation scheme is the simplest possible.
		   For example, if a region is watched for read and
		   a write watch is requested, a new watchpoint will
		   be used. Also, if a watch for a region that is already
		   covered by one or more existing watchpoints, a new
		   watchpoint will be used. */

		/* First, find a free data watchpoint. */
		for (bp = 0; bp < 6; bp++) {
			/* Each data watchpoint's control registers occupy 2 bits
			   (hence the 3), starting at bit 2 for D0 (hence the 2)
			   with 4 bits between for each watchpoint (yes, the 4). */
			if (!(sreg.s0_3 & (0x3 << (2 + (bp * 4))))) {
				break;
			}
		}

		if (bp > 5) {
			/* We're out of watchpoints. */
			gdb_cris_strcpy(output_buffer, error_message[E04]);
			return;
		}

		/* Configure the control register first. */
		if (type == '3' || type == '4') {
			/* Trigger on read. */
			sreg.s0_3 |= (1 << (2 + bp * 4));
		}
		if (type == '2' || type == '4') {
			/* Trigger on write. */
			sreg.s0_3 |= (2 << (2 + bp * 4));
		}

		/* Ugly pointer arithmetics to configure the watched range. */
		bp_d_regs[bp * 2] = addr;
		bp_d_regs[bp * 2 + 1] = (addr + len - 1);
	}

	/* Set the S1 flag to enable watchpoints. */
	reg.ccs |= (1 << (S_CCS_BITNR + CCS_SHIFT));
	gdb_cris_strcpy(output_buffer, "OK");
}