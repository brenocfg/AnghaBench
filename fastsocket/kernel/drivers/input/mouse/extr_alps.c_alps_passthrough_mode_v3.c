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
struct psmouse {int dummy; } ;

/* Variables and functions */
 int __alps_command_mode_write_reg (struct psmouse*,int) ; 
 int alps_command_mode_read_reg (struct psmouse*,int) ; 
 scalar_t__ alps_enter_command_mode (struct psmouse*) ; 
 scalar_t__ alps_exit_command_mode (struct psmouse*) ; 

__attribute__((used)) static int alps_passthrough_mode_v3(struct psmouse *psmouse,
				    int reg_base, bool enable)
{
	int reg_val, ret = -1;

	if (alps_enter_command_mode(psmouse))
		return -1;

	reg_val = alps_command_mode_read_reg(psmouse, reg_base + 0x0008);
	if (reg_val == -1)
		goto error;

	if (enable)
		reg_val |= 0x01;
	else
		reg_val &= ~0x01;

	ret = __alps_command_mode_write_reg(psmouse, reg_val);

error:
	if (alps_exit_command_mode(psmouse))
		ret = -1;
	return ret;
}