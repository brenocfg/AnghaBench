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
 int PSMOUSE_CMD_DISABLE ; 
 int PSMOUSE_CMD_SETSCALE11 ; 
 int PSMOUSE_CMD_SETSCALE21 ; 
 scalar_t__ ps2_command (struct ps2dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ps2_drain (struct ps2dev*,int,int) ; 

__attribute__((used)) static int alps_passthrough_mode_v2(struct psmouse *psmouse, bool enable)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	int cmd = enable ? PSMOUSE_CMD_SETSCALE21 : PSMOUSE_CMD_SETSCALE11;

	if (ps2_command(ps2dev, NULL, cmd) ||
	    ps2_command(ps2dev, NULL, cmd) ||
	    ps2_command(ps2dev, NULL, cmd) ||
	    ps2_command(ps2dev, NULL, PSMOUSE_CMD_DISABLE))
		return -1;

	/* we may get 3 more bytes, just ignore them */
	ps2_drain(ps2dev, 3, 100);

	return 0;
}