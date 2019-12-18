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
struct kgdb_state {int /*<<< orphan*/  linux_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  NUMREGBYTES ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  error_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gdb_regs ; 
 int /*<<< orphan*/  gdb_regs_to_pt_regs (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kgdb_hex2mem (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ kgdb_usethread ; 
 int /*<<< orphan*/ * remcom_in_buffer ; 
 int /*<<< orphan*/  remcom_out_buffer ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void gdb_cmd_setregs(struct kgdb_state *ks)
{
	kgdb_hex2mem(&remcom_in_buffer[1], (char *)gdb_regs, NUMREGBYTES);

	if (kgdb_usethread && kgdb_usethread != current) {
		error_packet(remcom_out_buffer, -EINVAL);
	} else {
		gdb_regs_to_pt_regs(gdb_regs, ks->linux_regs);
		strcpy(remcom_out_buffer, "OK");
	}
}