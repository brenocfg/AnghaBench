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
typedef  int /*<<< orphan*/  u8 ;
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LIS3L02DQ_DEC_MASK ; 
 int /*<<< orphan*/  LIS3L02DQ_REG_CTRL_1_ADDR ; 
 int /*<<< orphan*/  LIS3L02DQ_REG_CTRL_1_DF_128 ; 
 int /*<<< orphan*/  LIS3L02DQ_REG_CTRL_1_DF_32 ; 
 int /*<<< orphan*/  LIS3L02DQ_REG_CTRL_1_DF_64 ; 
 int /*<<< orphan*/  LIS3L02DQ_REG_CTRL_1_DF_8 ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int lis3l02dq_spi_read_reg_8 (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int lis3l02dq_spi_write_reg_8 (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strict_strtol (char const*,int,long*) ; 

__attribute__((used)) static ssize_t lis3l02dq_write_frequency(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf,
					 size_t len)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	long val;
	int ret;
	u8 t;

	ret = strict_strtol(buf, 10, &val);
	if (ret)
		return ret;

	mutex_lock(&indio_dev->mlock);
	ret = lis3l02dq_spi_read_reg_8(dev,
				       LIS3L02DQ_REG_CTRL_1_ADDR,
				       &t);
	if (ret)
		goto error_ret_mutex;
	/* Wipe the bits clean */
	t &= ~LIS3L02DQ_DEC_MASK;
	switch (val) {
	case 280:
		t |= LIS3L02DQ_REG_CTRL_1_DF_128;
		break;
	case 560:
		t |= LIS3L02DQ_REG_CTRL_1_DF_64;
		break;
	case 1120:
		t |= LIS3L02DQ_REG_CTRL_1_DF_32;
		break;
	case 4480:
		t |= LIS3L02DQ_REG_CTRL_1_DF_8;
		break;
	default:
		ret = -EINVAL;
		goto error_ret_mutex;
	};

	ret = lis3l02dq_spi_write_reg_8(dev,
					LIS3L02DQ_REG_CTRL_1_ADDR,
					&t);

error_ret_mutex:
	mutex_unlock(&indio_dev->mlock);

	return ret ? ret : len;
}