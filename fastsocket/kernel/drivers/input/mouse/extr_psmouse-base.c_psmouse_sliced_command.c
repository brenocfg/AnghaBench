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
 int /*<<< orphan*/  PSMOUSE_CMD_SETRES ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETSCALE11 ; 
 scalar_t__ ps2_command (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 

int psmouse_sliced_command(struct psmouse *psmouse, unsigned char command)
{
	int i;

	if (ps2_command(&psmouse->ps2dev, NULL, PSMOUSE_CMD_SETSCALE11))
		return -1;

	for (i = 6; i >= 0; i -= 2) {
		unsigned char d = (command >> i) & 3;
		if (ps2_command(&psmouse->ps2dev, &d, PSMOUSE_CMD_SETRES))
			return -1;
	}

	return 0;
}