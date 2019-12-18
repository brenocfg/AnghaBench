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
 int PSMOUSE_CMD_POLL ; 
 scalar_t__ ps2_command (int /*<<< orphan*/ *,unsigned char*,int) ; 
 scalar_t__ psmouse_sliced_command (struct psmouse*,unsigned char) ; 

__attribute__((used)) static int ps2pp_cmd(struct psmouse *psmouse, unsigned char *param, unsigned char command)
{
	if (psmouse_sliced_command(psmouse, command))
		return -1;

	if (ps2_command(&psmouse->ps2dev, param, PSMOUSE_CMD_POLL | 0x0300))
		return -1;

	return 0;
}