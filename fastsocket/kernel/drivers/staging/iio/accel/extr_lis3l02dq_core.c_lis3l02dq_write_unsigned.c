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
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  u8 ;
struct iio_dev_attr {int /*<<< orphan*/  address; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int lis3l02dq_spi_write_reg_8 (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int strict_strtoul (char const*,int,int /*<<< orphan*/ *) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t lis3l02dq_write_unsigned(struct device *dev,
					struct device_attribute *attr,
					const char *buf,
					size_t len)
{
	int ret;
	ulong valin;
	u8 val;
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);

	ret = strict_strtoul(buf, 10, &valin);
	if (ret)
		goto err_ret;
	val = valin;
	ret = lis3l02dq_spi_write_reg_8(dev, this_attr->address, &val);

err_ret:
	return ret ? ret : len;
}