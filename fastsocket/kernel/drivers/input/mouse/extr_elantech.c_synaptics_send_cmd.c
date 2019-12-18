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
struct psmouse {int /*<<< orphan*/  ps2dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSMOUSE_CMD_GETINFO ; 
 int /*<<< orphan*/  pr_err (char*,unsigned char) ; 
 scalar_t__ ps2_command (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ psmouse_sliced_command (struct psmouse*,unsigned char) ; 

__attribute__((used)) static int synaptics_send_cmd(struct psmouse *psmouse, unsigned char c,
				unsigned char *param)
{
	if (psmouse_sliced_command(psmouse, c) ||
	    ps2_command(&psmouse->ps2dev, param, PSMOUSE_CMD_GETINFO)) {
		pr_err("elantech.c: synaptics_send_cmd query 0x%02x failed.\n", c);
		return -1;
	}

	return 0;
}