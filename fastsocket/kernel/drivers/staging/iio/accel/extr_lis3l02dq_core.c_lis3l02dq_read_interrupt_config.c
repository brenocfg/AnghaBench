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
struct iio_event_attr {int mask; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  int s8 ;

/* Variables and functions */
 int /*<<< orphan*/  LIS3L02DQ_REG_WAKE_UP_CFG_ADDR ; 
 int lis3l02dq_spi_read_reg_8 (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int) ; 
 struct iio_event_attr* to_iio_event_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t lis3l02dq_read_interrupt_config(struct device *dev,
					       struct device_attribute *attr,
					       char *buf)
{
	int ret;
	s8 val;
	struct iio_event_attr *this_attr = to_iio_event_attr(attr);

	ret = lis3l02dq_spi_read_reg_8(dev,
				       LIS3L02DQ_REG_WAKE_UP_CFG_ADDR,
				       (u8 *)&val);

	return ret ? ret : sprintf(buf, "%d\n",
				   (val & this_attr->mask) ? 1 : 0);;
}