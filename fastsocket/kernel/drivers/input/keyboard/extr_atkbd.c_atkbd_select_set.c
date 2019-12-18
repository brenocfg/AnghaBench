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
struct atkbd {int extra; int id; scalar_t__ translated; struct ps2dev ps2dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATKBD_CMD_EX_ENABLE ; 
 int /*<<< orphan*/  ATKBD_CMD_GSCANSET ; 
 int /*<<< orphan*/  ATKBD_CMD_OK_GETID ; 
 int /*<<< orphan*/  ATKBD_CMD_SETALL_MBR ; 
 int /*<<< orphan*/  ATKBD_CMD_SSCANSET ; 
 scalar_t__ ps2_command (struct ps2dev*,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atkbd_select_set(struct atkbd *atkbd, int target_set, int allow_extra)
{
	struct ps2dev *ps2dev = &atkbd->ps2dev;
	unsigned char param[2];

	atkbd->extra = 0;
/*
 * For known special keyboards we can go ahead and set the correct set.
 * We check for NCD PS/2 Sun, NorthGate OmniKey 101 and
 * IBM RapidAccess / IBM EzButton / Chicony KBP-8993 keyboards.
 */

	if (atkbd->translated)
		return 2;

	if (atkbd->id == 0xaca1) {
		param[0] = 3;
		ps2_command(ps2dev, param, ATKBD_CMD_SSCANSET);
		return 3;
	}

	if (allow_extra) {
		param[0] = 0x71;
		if (!ps2_command(ps2dev, param, ATKBD_CMD_EX_ENABLE)) {
			atkbd->extra = 1;
			return 2;
		}
	}

	if (target_set != 3)
		return 2;

	if (!ps2_command(ps2dev, param, ATKBD_CMD_OK_GETID)) {
		atkbd->id = param[0] << 8 | param[1];
		return 2;
	}

	param[0] = 3;
	if (ps2_command(ps2dev, param, ATKBD_CMD_SSCANSET))
		return 2;

	param[0] = 0;
	if (ps2_command(ps2dev, param, ATKBD_CMD_GSCANSET))
		return 2;

	if (param[0] != 3) {
		param[0] = 2;
		if (ps2_command(ps2dev, param, ATKBD_CMD_SSCANSET))
		return 2;
	}

	ps2_command(ps2dev, param, ATKBD_CMD_SETALL_MBR);

	return 3;
}