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
 scalar_t__ lifebook_use_6byte_proto ; 
 int /*<<< orphan*/  ps2_command (struct ps2dev*,unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ psmouse_reset (struct psmouse*) ; 

__attribute__((used)) static int lifebook_absolute_mode(struct psmouse *psmouse)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned char param;

	if (psmouse_reset(psmouse))
		return -1;

	/*
	   Enable absolute output -- ps2_command fails always but if
	   you leave this call out the touchsreen will never send
	   absolute coordinates
	*/
	param = lifebook_use_6byte_proto ? 0x08 : 0x07;
	ps2_command(ps2dev, &param, PSMOUSE_CMD_SETRES);

	return 0;
}