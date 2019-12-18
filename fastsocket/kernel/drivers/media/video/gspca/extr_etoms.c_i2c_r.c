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
struct gspca_dev {int dummy; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ET_I2C_BASE ; 
 int /*<<< orphan*/  ET_I2C_COUNT ; 
 int /*<<< orphan*/  ET_I2C_DATA0 ; 
 int /*<<< orphan*/  ET_I2C_PREFETCH ; 
 int /*<<< orphan*/  ET_I2C_REG ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_w_val (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i2c_r(struct gspca_dev *gspca_dev,
			__u8 reg)
{
	/* set the base address */
	reg_w_val(gspca_dev, ET_I2C_BASE, 0x40);
					/* sensor base for the pas106 */
	/* set count and prefetch (cnd: 4 bits - mode: 4 bits) */
	reg_w_val(gspca_dev, ET_I2C_COUNT, 0x11);
	reg_w_val(gspca_dev, ET_I2C_REG, reg);	/* set the register base */
	reg_w_val(gspca_dev, ET_I2C_PREFETCH, 0x02);	/* prefetch */
	reg_w_val(gspca_dev, ET_I2C_PREFETCH, 0x00);
	reg_r(gspca_dev, ET_I2C_DATA0, 1);	/* read one byte */
	return 0;
}