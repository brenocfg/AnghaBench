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
 int /*<<< orphan*/  PSMOUSE_CMD_RESET_BAT ; 
 unsigned char PSMOUSE_RET_BAT ; 
 unsigned char PSMOUSE_RET_ID ; 
 scalar_t__ ps2_command (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 

int psmouse_reset(struct psmouse *psmouse)
{
	unsigned char param[2];

	if (ps2_command(&psmouse->ps2dev, param, PSMOUSE_CMD_RESET_BAT))
		return -1;

	if (param[0] != PSMOUSE_RET_BAT && param[1] != PSMOUSE_RET_ID)
		return -1;

	return 0;
}