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
struct sca3000_state {int dummy; } ;
struct iio_dev {struct sca3000_state* dev_data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCA3000_REG_ADDR_TEMP_MSB ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int sca3000_read_data (struct sca3000_state*,int /*<<< orphan*/ ,int**,int) ; 
 scalar_t__ sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t sca3000_read_temp(struct device *dev,
				 struct device_attribute *attr,
				 char *buf)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct sca3000_state *st = indio_dev->dev_data;
	int len = 0, ret;
	int val;
	u8 *rx;
	ret = sca3000_read_data(st, SCA3000_REG_ADDR_TEMP_MSB, &rx, 2);
	if (ret < 0)
		goto error_ret;
	val = ((rx[1]&0x3F) << 3) | ((rx[2] & 0xE0) >> 5);
	len += sprintf(buf + len, "%d\n", val);
	kfree(rx);

	return len;

error_ret:
	return ret;
}