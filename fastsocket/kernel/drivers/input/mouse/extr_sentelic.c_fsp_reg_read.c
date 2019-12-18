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
struct ps2dev {TYPE_1__* serio; } ;
struct psmouse {struct ps2dev ps2dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSP_CMD_TIMEOUT ; 
 int /*<<< orphan*/  FSP_CMD_TIMEOUT2 ; 
 int /*<<< orphan*/  PSMOUSE_ACTIVATED ; 
 int /*<<< orphan*/  PSMOUSE_CMD_DISABLE ; 
 int /*<<< orphan*/  PSMOUSE_CMD_ENABLE ; 
 int /*<<< orphan*/  PSMOUSE_CMD_GETINFO ; 
 int /*<<< orphan*/  PSMOUSE_CMD_MODE ; 
 scalar_t__ __ps2_command (struct ps2dev*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int) ; 
 unsigned char fsp_test_invert_cmd (int) ; 
 unsigned char fsp_test_swap_cmd (int) ; 
 int /*<<< orphan*/  ps2_begin_command (struct ps2dev*) ; 
 int /*<<< orphan*/  ps2_command (struct ps2dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps2_end_command (struct ps2dev*) ; 
 scalar_t__ ps2_sendbyte (struct ps2dev*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_set_state (struct psmouse*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsp_reg_read(struct psmouse *psmouse, int reg_addr, int *reg_val)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	unsigned char param[3];
	unsigned char addr;
	int rc = -1;

	/*
	 * We need to shut off the device and switch it into command
	 * mode so we don't confuse our protocol handler. We don't need
	 * to do that for writes because sysfs set helper does this for
	 * us.
	 */
	ps2_command(ps2dev, NULL, PSMOUSE_CMD_DISABLE);
	psmouse_set_state(psmouse, PSMOUSE_CMD_MODE);

	ps2_begin_command(ps2dev);

	if (ps2_sendbyte(ps2dev, 0xf3, FSP_CMD_TIMEOUT) < 0)
		goto out;

	/* should return 0xfe(request for resending) */
	ps2_sendbyte(ps2dev, 0x66, FSP_CMD_TIMEOUT2);
	/* should return 0xfc(failed) */
	ps2_sendbyte(ps2dev, 0x88, FSP_CMD_TIMEOUT2);

	if (ps2_sendbyte(ps2dev, 0xf3, FSP_CMD_TIMEOUT) < 0)
		goto out;

	if ((addr = fsp_test_invert_cmd(reg_addr)) != reg_addr) {
		ps2_sendbyte(ps2dev, 0x68, FSP_CMD_TIMEOUT2);
	} else if ((addr = fsp_test_swap_cmd(reg_addr)) != reg_addr) {
		/* swapping is required */
		ps2_sendbyte(ps2dev, 0xcc, FSP_CMD_TIMEOUT2);
		/* expect 0xfe */
	} else {
		/* swapping isn't necessary */
		ps2_sendbyte(ps2dev, 0x66, FSP_CMD_TIMEOUT2);
		/* expect 0xfe */
	}
	/* should return 0xfc(failed) */
	ps2_sendbyte(ps2dev, addr, FSP_CMD_TIMEOUT);

	if (__ps2_command(ps2dev, param, PSMOUSE_CMD_GETINFO) < 0)
		goto out;

	*reg_val = param[2];
	rc = 0;

 out:
	ps2_end_command(ps2dev);
	ps2_command(ps2dev, NULL, PSMOUSE_CMD_ENABLE);
	psmouse_set_state(psmouse, PSMOUSE_ACTIVATED);
	dev_dbg(&ps2dev->serio->dev, "READ REG: 0x%02x is 0x%02x (rc = %d)\n",
		reg_addr, *reg_val, rc);
	return rc;
}