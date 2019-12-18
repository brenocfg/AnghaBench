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
struct ps2dev {int dummy; } ;
struct psmouse {char* vendor; char* name; int pktsize; TYPE_1__* dev; struct ps2dev ps2dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  relbit; int /*<<< orphan*/  keybit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_EXTRA ; 
 int /*<<< orphan*/  BTN_SIDE ; 
 int /*<<< orphan*/  PSMOUSE_CMD_GETINFO ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETRES ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETSCALE11 ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps2_command (struct ps2dev*,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int genius_detect(struct psmouse *psmouse, bool set_properties)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned char param[4];

	param[0] = 3;
	ps2_command(ps2dev, param, PSMOUSE_CMD_SETRES);
	ps2_command(ps2dev,  NULL, PSMOUSE_CMD_SETSCALE11);
	ps2_command(ps2dev,  NULL, PSMOUSE_CMD_SETSCALE11);
	ps2_command(ps2dev,  NULL, PSMOUSE_CMD_SETSCALE11);
	ps2_command(ps2dev, param, PSMOUSE_CMD_GETINFO);

	if (param[0] != 0x00 || param[1] != 0x33 || param[2] != 0x55)
		return -1;

	if (set_properties) {
		__set_bit(BTN_EXTRA, psmouse->dev->keybit);
		__set_bit(BTN_SIDE, psmouse->dev->keybit);
		__set_bit(REL_WHEEL, psmouse->dev->relbit);

		psmouse->vendor = "Genius";
		psmouse->name = "Mouse";
		psmouse->pktsize = 4;
	}

	return 0;
}