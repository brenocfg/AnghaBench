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
struct usb_ov511 {int dummy; } ;
struct ov511_regvals {scalar_t__ bus; int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 scalar_t__ OV511_DONE_BUS ; 
 scalar_t__ OV511_I2C_BUS ; 
 scalar_t__ OV511_REG_BUS ; 
 int /*<<< orphan*/  err (char*) ; 
 int i2c_w (struct usb_ov511*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int reg_w (struct usb_ov511*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
write_regvals(struct usb_ov511 *ov, struct ov511_regvals * pRegvals)
{
	int rc;

	while (pRegvals->bus != OV511_DONE_BUS) {
		if (pRegvals->bus == OV511_REG_BUS) {
			if ((rc = reg_w(ov, pRegvals->reg, pRegvals->val)) < 0)
				return rc;
		} else if (pRegvals->bus == OV511_I2C_BUS) {
			if ((rc = i2c_w(ov, pRegvals->reg, pRegvals->val)) < 0)
				return rc;
		} else {
			err("Bad regval array");
			return -1;
		}
		pRegvals++;
	}
	return 0;
}