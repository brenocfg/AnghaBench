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
struct iio_dev {struct sca3000_state* dev_data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCA3000_REG_ADDR_REVID ; 
 int SCA3000_REVID_MAJOR_MASK ; 
 int SCA3000_REVID_MINOR_MASK ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sca3000_read_data (struct sca3000_state*,int /*<<< orphan*/ ,int**,int) ; 
 scalar_t__ sprintf (char*,char*,int,int) ; 

__attribute__((used)) static ssize_t sca3000_show_rev(struct device *dev,
				struct device_attribute *attr,
				char *buf)
{
	int len = 0, ret;
	struct iio_dev *dev_info = dev_get_drvdata(dev);
	struct sca3000_state *st = dev_info->dev_data;

	u8 *rx;

	mutex_lock(&st->lock);
	ret = sca3000_read_data(st, SCA3000_REG_ADDR_REVID, &rx, 1);
	if (ret < 0)
		goto error_ret;
	len += sprintf(buf + len,
		       "major=%d, minor=%d\n",
		       rx[1] & SCA3000_REVID_MAJOR_MASK,
		       rx[1] & SCA3000_REVID_MINOR_MASK);
	kfree(rx);

error_ret:
	mutex_unlock(&st->lock);

	return ret ? ret : len;
}