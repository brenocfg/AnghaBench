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
struct psmouse {int resolution; struct ps2dev ps2dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSMOUSE_CMD_SETRES ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETSCALE11 ; 
 int /*<<< orphan*/  ps2_command (struct ps2dev*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_set_resolution (struct psmouse*,unsigned int) ; 

__attribute__((used)) static void ps2pp_set_resolution(struct psmouse *psmouse, unsigned int resolution)
{
	if (resolution > 400) {
		struct ps2dev *ps2dev = &psmouse->ps2dev;
		unsigned char param = 3;

		ps2_command(ps2dev, NULL, PSMOUSE_CMD_SETSCALE11);
		ps2_command(ps2dev, NULL, PSMOUSE_CMD_SETSCALE11);
		ps2_command(ps2dev, NULL, PSMOUSE_CMD_SETSCALE11);
		ps2_command(ps2dev, &param, PSMOUSE_CMD_SETRES);
		psmouse->resolution = 800;
	} else
		psmouse_set_resolution(psmouse, resolution);
}