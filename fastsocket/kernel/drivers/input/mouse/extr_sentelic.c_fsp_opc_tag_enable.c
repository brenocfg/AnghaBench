#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__* serio; } ;
struct psmouse {TYPE_1__ ps2dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int FSP_BIT_EN_OPC_TAG ; 
 int /*<<< orphan*/  FSP_REG_OPC_QDOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int fsp_reg_read (struct psmouse*,int /*<<< orphan*/ ,int*) ; 
 int fsp_reg_write (struct psmouse*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fsp_reg_write_enable (struct psmouse*,int) ; 

__attribute__((used)) static int fsp_opc_tag_enable(struct psmouse *psmouse, bool enable)
{
	int v, nv;
	int res = 0;

	if (fsp_reg_read(psmouse, FSP_REG_OPC_QDOWN, &v) == -1) {
		dev_err(&psmouse->ps2dev.serio->dev, "Unable get OPC state.\n");
		return -EIO;
	}

	if (enable)
		nv = v | FSP_BIT_EN_OPC_TAG;
	else
		nv = v & ~FSP_BIT_EN_OPC_TAG;

	/* only write if necessary */
	if (nv != v) {
		fsp_reg_write_enable(psmouse, true);
		res = fsp_reg_write(psmouse, FSP_REG_OPC_QDOWN, nv);
		fsp_reg_write_enable(psmouse, false);
	}

	if (res != 0) {
		dev_err(&psmouse->ps2dev.serio->dev,
			"Unable to enable OPC tag.\n");
		res = -EIO;
	}

	return res;
}