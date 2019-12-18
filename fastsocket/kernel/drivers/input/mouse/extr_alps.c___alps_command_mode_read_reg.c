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
 int /*<<< orphan*/  PSMOUSE_CMD_GETINFO ; 
 scalar_t__ ps2_command (struct ps2dev*,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __alps_command_mode_read_reg(struct psmouse *psmouse, int addr)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned char param[4];

	if (ps2_command(ps2dev, param, PSMOUSE_CMD_GETINFO))
		return -1;

	/*
	 * The address being read is returned in the first two bytes
	 * of the result. Check that this address matches the expected
	 * address.
	 */
	if (addr != ((param[0] << 8) | param[1]))
		return -1;

	return param[2];
}