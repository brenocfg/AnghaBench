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
struct ps2dev {int dummy; } ;
struct psmouse {struct ps2dev ps2dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSMOUSE_CMD_SETRES ; 
 int /*<<< orphan*/  ps2_command (struct ps2dev*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps2pp_cmd (struct psmouse*,unsigned char*,int) ; 

__attribute__((used)) static void ps2pp_set_smartscroll(struct psmouse *psmouse, bool smartscroll)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned char param[4];

	ps2pp_cmd(psmouse, param, 0x32);

	param[0] = 0;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES);
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES);
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES);

	param[0] = smartscroll;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES);
}