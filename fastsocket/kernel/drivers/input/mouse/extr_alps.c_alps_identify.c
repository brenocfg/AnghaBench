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
struct psmouse {struct alps_data* private; } ;
struct alps_data {void* proto_version; int /*<<< orphan*/  flags; int /*<<< orphan*/  decode_fields; int /*<<< orphan*/  hw_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALPS_DUALPOINT ; 
 void* ALPS_PROTO_V3 ; 
 void* ALPS_PROTO_V5 ; 
 int /*<<< orphan*/  ALPS_REG_BASE_RUSHMORE ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  PSMOUSE_CMD_RESET_WRAP ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETRES ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETSCALE11 ; 
 int /*<<< orphan*/  PSMOUSE_CMD_SETSCALE21 ; 
 int /*<<< orphan*/  alps_decode_rushmore ; 
 scalar_t__ alps_exit_command_mode (struct psmouse*) ; 
 int /*<<< orphan*/  alps_hw_init_rushmore_v3 ; 
 scalar_t__ alps_match_table (struct psmouse*,struct alps_data*,unsigned char*,unsigned char*) ; 
 scalar_t__ alps_probe_trackstick_v3 (struct psmouse*,int /*<<< orphan*/ ) ; 
 scalar_t__ alps_rpt_cmd (struct psmouse*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  alps_set_defaults (struct alps_data*) ; 
 int /*<<< orphan*/  dbg (char*,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char) ; 

__attribute__((used)) static int alps_identify(struct psmouse *psmouse, struct alps_data *priv)
{
	unsigned char e6[4], e7[4], ec[4];

	/*
	 * First try "E6 report".
	 * ALPS should return 0,0,10 or 0,0,100 if no buttons are pressed.
	 * The bits 0-2 of the first byte will be 1s if some buttons are
	 * pressed.
	 */
	if (alps_rpt_cmd(psmouse, PSMOUSE_CMD_SETRES,
			 PSMOUSE_CMD_SETSCALE11, e6))
		return -EIO;

	if ((e6[0] & 0xf8) != 0 || e6[1] != 0 || (e6[2] != 10 && e6[2] != 100))
		return -EINVAL;

	/*
	 * Now get the "E7" and "EC" reports.  These will uniquely identify
	 * most ALPS touchpads.
	 */
	if (alps_rpt_cmd(psmouse, PSMOUSE_CMD_SETRES,
			 PSMOUSE_CMD_SETSCALE21, e7) ||
	    alps_rpt_cmd(psmouse, PSMOUSE_CMD_SETRES,
			 PSMOUSE_CMD_RESET_WRAP, ec) ||
	    alps_exit_command_mode(psmouse))
		return -EIO;

	if (alps_match_table(psmouse, priv, e7, ec) == 0) {
		return 0;
	} else if (e7[0] == 0x73 && e7[1] == 0x03 && e7[2] == 0x50 &&
		   ec[0] == 0x73 && ec[1] == 0x01) {
		priv->proto_version = ALPS_PROTO_V5;
		alps_set_defaults(priv);

		return 0;
	} else if (ec[0] == 0x88 && ec[1] == 0x08) {
		priv->proto_version = ALPS_PROTO_V3;
		alps_set_defaults(priv);

		priv->hw_init = alps_hw_init_rushmore_v3;
		priv->decode_fields = alps_decode_rushmore;

		/* hack to make addr_command, nibble_command available */
		psmouse->private = priv;

		if (alps_probe_trackstick_v3(psmouse, ALPS_REG_BASE_RUSHMORE))
			priv->flags &= ~ALPS_DUALPOINT;

		return 0;
	} else if (ec[0] == 0x88 && ec[1] == 0x07 &&
		   ec[2] >= 0x90 && ec[2] <= 0x9d) {
		priv->proto_version = ALPS_PROTO_V3;
		alps_set_defaults(priv);

		return 0;
	}

	dbg("Unknown ALPS touchpad: E7=%2.2x %2.2x %2.2x, EC=%2.2x %2.2x %2.2x\n",
	    e7[0], e7[1], e7[2], ec[0], ec[1], ec[2]);

	return -EINVAL;
}