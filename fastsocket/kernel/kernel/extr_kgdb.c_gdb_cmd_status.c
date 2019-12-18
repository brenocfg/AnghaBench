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
struct kgdb_state {int /*<<< orphan*/  signo; } ;

/* Variables and functions */
 int /*<<< orphan*/  pack_hex_byte (char*,int /*<<< orphan*/ ) ; 
 char* remcom_out_buffer ; 
 int /*<<< orphan*/  remove_all_break () ; 

__attribute__((used)) static void gdb_cmd_status(struct kgdb_state *ks)
{
	/*
	 * We know that this packet is only sent
	 * during initial connect.  So to be safe,
	 * we clear out our breakpoints now in case
	 * GDB is reconnecting.
	 */
	remove_all_break();

	remcom_out_buffer[0] = 'S';
	pack_hex_byte(&remcom_out_buffer[1], ks->signo);
}