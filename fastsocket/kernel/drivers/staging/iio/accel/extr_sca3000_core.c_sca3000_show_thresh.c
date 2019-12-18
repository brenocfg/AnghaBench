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
struct sca3000_state {int /*<<< orphan*/  lock; } ;
struct iio_dev_attr {int /*<<< orphan*/  address; } ;
struct iio_dev {struct sca3000_state* dev_data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sca3000_read_ctrl_reg (struct sca3000_state*,int /*<<< orphan*/ ,int**) ; 
 scalar_t__ sprintf (char*,char*,int) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t sca3000_show_thresh(struct device *dev,
				   struct device_attribute *attr,
				   char *buf)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct sca3000_state *st = indio_dev->dev_data;
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	int len = 0, ret;
	u8 *rx;

	mutex_lock(&st->lock);
	ret = sca3000_read_ctrl_reg(st,
				    this_attr->address,
				    &rx);
	mutex_unlock(&st->lock);
	if (ret)
		return ret;
	len += sprintf(buf + len, "%d\n", rx[1]);
	kfree(rx);

	return len;
}