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
struct psmouse {int /*<<< orphan*/  ps2dev; struct elantech_data* private; } ;
struct elantech_data {int hw_version; } ;

/* Variables and functions */
 unsigned char ETP_PS2_CUSTOM_COMMAND ; 
 unsigned char ETP_REGISTER_WRITE ; 
 unsigned char PSMOUSE_CMD_SETSCALE11 ; 
 int /*<<< orphan*/  elantech_ps2_command (struct psmouse*,int /*<<< orphan*/ *,unsigned char) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  ps2_command (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char) ; 
 int /*<<< orphan*/  psmouse_sliced_command (struct psmouse*,unsigned char) ; 

__attribute__((used)) static int elantech_write_reg(struct psmouse *psmouse, unsigned char reg,
				unsigned char val)
{
	struct elantech_data *etd = psmouse->private;
	int rc = 0;

	if (reg < 0x10 || reg > 0x26)
		return -1;

	if (reg > 0x11 && reg < 0x20)
		return -1;

	switch (etd->hw_version) {
	case 1:
		if (psmouse_sliced_command(psmouse, ETP_REGISTER_WRITE) ||
		    psmouse_sliced_command(psmouse, reg) ||
		    psmouse_sliced_command(psmouse, val) ||
		    ps2_command(&psmouse->ps2dev, NULL, PSMOUSE_CMD_SETSCALE11)) {
			rc = -1;
		}
		break;

	case 2:
		if (elantech_ps2_command(psmouse, NULL, ETP_PS2_CUSTOM_COMMAND) ||
		    elantech_ps2_command(psmouse, NULL, ETP_REGISTER_WRITE) ||
		    elantech_ps2_command(psmouse, NULL, ETP_PS2_CUSTOM_COMMAND) ||
		    elantech_ps2_command(psmouse, NULL, reg) ||
		    elantech_ps2_command(psmouse, NULL, ETP_PS2_CUSTOM_COMMAND) ||
		    elantech_ps2_command(psmouse, NULL, val) ||
		    elantech_ps2_command(psmouse, NULL, PSMOUSE_CMD_SETSCALE11)) {
			rc = -1;
		}
		break;
	}

	if (rc)
		pr_err("elantech.c: failed to write register 0x%02x with value 0x%02x.\n",
			reg, val);

	return rc;
}