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
typedef  enum hgpk_model_t { ____Placeholder_hgpk_model_t } hgpk_model_t ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  PSMOUSE_CMD_GETINFO ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETSCALE21 ; 
 int /*<<< orphan*/  hgpk_dbg (struct psmouse*,char*,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  hgpk_info (struct psmouse*,char*,unsigned char) ; 
 scalar_t__ ps2_command (struct ps2dev*,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum hgpk_model_t hgpk_get_model(struct psmouse *psmouse)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned char param[3];

	/* E7, E7, E7, E9 gets us a 3 byte identifier */
	if (ps2_command(ps2dev,  NULL, PSMOUSE_CMD_SETSCALE21) ||
	    ps2_command(ps2dev,  NULL, PSMOUSE_CMD_SETSCALE21) ||
	    ps2_command(ps2dev,  NULL, PSMOUSE_CMD_SETSCALE21) ||
	    ps2_command(ps2dev, param, PSMOUSE_CMD_GETINFO)) {
		return -EIO;
	}

	hgpk_dbg(psmouse, "ID: %02x %02x %02x\n", param[0], param[1], param[2]);

	/* HGPK signature: 0x67, 0x00, 0x<model> */
	if (param[0] != 0x67 || param[1] != 0x00)
		return -ENODEV;

	hgpk_info(psmouse, "OLPC touchpad revision 0x%x\n", param[2]);

	return param[2];
}