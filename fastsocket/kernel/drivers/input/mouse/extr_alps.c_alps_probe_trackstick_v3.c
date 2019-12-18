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
 int EIO ; 
 int ENODEV ; 
 int alps_command_mode_read_reg (struct psmouse*,int) ; 
 scalar_t__ alps_enter_command_mode (struct psmouse*) ; 
 int /*<<< orphan*/  alps_exit_command_mode (struct psmouse*) ; 

__attribute__((used)) static int alps_probe_trackstick_v3(struct psmouse *psmouse, int reg_base)
{
	int ret = -EIO, reg_val;

	if (alps_enter_command_mode(psmouse))
		goto error;

	reg_val = alps_command_mode_read_reg(psmouse, reg_base + 0x08);
	if (reg_val == -1)
		goto error;

	/* bit 7: trackstick is present */
	ret = reg_val & 0x80 ? 0 : -ENODEV;

error:
	alps_exit_command_mode(psmouse);
	return ret;
}