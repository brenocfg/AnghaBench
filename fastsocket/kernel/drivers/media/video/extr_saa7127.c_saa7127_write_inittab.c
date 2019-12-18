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
struct v4l2_subdev {int dummy; } ;
struct i2c_reg_value {scalar_t__ reg; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  saa7127_write (struct v4l2_subdev*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int saa7127_write_inittab(struct v4l2_subdev *sd,
				 const struct i2c_reg_value *regs)
{
	while (regs->reg != 0) {
		saa7127_write(sd, regs->reg, regs->value);
		regs++;
	}
	return 0;
}