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
typedef  int u8 ;
struct iio_scan_el {int label; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LIS3L02DQ_REG_CTRL_1_ADDR ; 
 int LIS3L02DQ_REG_CTRL_1_AXES_X_ENABLE ; 
 int LIS3L02DQ_REG_CTRL_1_AXES_Y_ENABLE ; 
 int LIS3L02DQ_REG_CTRL_1_AXES_Z_ENABLE ; 
#define  LIS3L02DQ_REG_OUT_X_L_ADDR 130 
#define  LIS3L02DQ_REG_OUT_Y_L_ADDR 129 
#define  LIS3L02DQ_REG_OUT_Z_L_ADDR 128 
 int lis3l02dq_spi_read_reg_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int lis3l02dq_spi_write_reg_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int lis3l02dq_scan_el_set_state(struct iio_scan_el *scan_el,
				       struct iio_dev *indio_dev,
				       bool state)
{
	u8 t, mask;
	int ret;

	ret = lis3l02dq_spi_read_reg_8(&indio_dev->dev,
				       LIS3L02DQ_REG_CTRL_1_ADDR,
				       &t);
	if (ret)
		goto error_ret;
	switch (scan_el->label) {
	case LIS3L02DQ_REG_OUT_X_L_ADDR:
		mask = LIS3L02DQ_REG_CTRL_1_AXES_X_ENABLE;
		break;
	case LIS3L02DQ_REG_OUT_Y_L_ADDR:
		mask = LIS3L02DQ_REG_CTRL_1_AXES_Y_ENABLE;
		break;
	case LIS3L02DQ_REG_OUT_Z_L_ADDR:
		mask = LIS3L02DQ_REG_CTRL_1_AXES_Z_ENABLE;
		break;
	default:
		ret = -EINVAL;
		goto error_ret;
	}

	if (!(mask & t) == state) {
		if (state)
			t |= mask;
		else
			t &= ~mask;
		ret = lis3l02dq_spi_write_reg_8(&indio_dev->dev,
						LIS3L02DQ_REG_CTRL_1_ADDR,
						&t);
	}
error_ret:
	return ret;

}