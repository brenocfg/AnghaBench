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
struct iio_dev_attr {int /*<<< orphan*/  address; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int lis3l02dq_spi_read_reg_8 (struct device*,int /*<<< orphan*/ ,int*) ; 
 int sprintf (char*,char*,int) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t lis3l02dq_read_unsigned(struct device *dev,
				       struct device_attribute *attr,
				       char *buf)
{
	int ret;
	u8 val;
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);

	ret = lis3l02dq_spi_read_reg_8(dev, this_attr->address, &val);

	return ret ? ret : sprintf(buf, "%d\n", val);
}