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
struct TYPE_2__ {int /*<<< orphan*/  fw_ver_str; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ISA_VERSION_HUNDRETH ; 
 int /*<<< orphan*/  CMD_ISA_VERSION_INTEGER ; 
 int /*<<< orphan*/  CMD_ISA_VERSION_MINOR ; 
 int /*<<< orphan*/  CMD_ISA_VERSION_TENTH ; 
 TYPE_1__ pcwd_private ; 
 int send_isa_command (int /*<<< orphan*/ ) ; 
 scalar_t__ set_command_mode () ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unset_command_mode () ; 

__attribute__((used)) static inline void pcwd_get_firmware(void)
{
	int one, ten, hund, minor;

	strcpy(pcwd_private.fw_ver_str, "ERROR");

	if (set_command_mode()) {
		one = send_isa_command(CMD_ISA_VERSION_INTEGER);
		ten = send_isa_command(CMD_ISA_VERSION_TENTH);
		hund = send_isa_command(CMD_ISA_VERSION_HUNDRETH);
		minor = send_isa_command(CMD_ISA_VERSION_MINOR);
		sprintf(pcwd_private.fw_ver_str, "%c.%c%c%c",
					one, ten, hund, minor);
	}
	unset_command_mode();

	return;
}