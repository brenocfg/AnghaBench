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
 int SCA3000_FREE_FALL_DETECT ; 
 int /*<<< orphan*/  SCA3000_REG_ADDR_MODE ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sca3000_read_data (struct sca3000_state*,int /*<<< orphan*/ ,int**,int) ; 
 int sca3000_write_reg (struct sca3000_state*,int /*<<< orphan*/ ,int) ; 
 int strict_strtol (char const*,int,long*) ; 

__attribute__((used)) static ssize_t sca3000_set_free_fall_mode(struct device *dev,
					  struct device_attribute *attr,
					  const char *buf,
					  size_t len)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct sca3000_state *st = indio_dev->dev_data;
	long val;
	int ret;
	u8 *rx;
	u8 protect_mask = SCA3000_FREE_FALL_DETECT;

	mutex_lock(&st->lock);
	ret = strict_strtol(buf, 10, &val);
	if (ret)
		goto error_ret;

	/* read current value of mode register */
	ret = sca3000_read_data(st, SCA3000_REG_ADDR_MODE, &rx, 1);
	if (ret)
		goto error_ret;

	/*if off and should be on*/
	if (val && !(rx[1] & protect_mask))
		ret = sca3000_write_reg(st, SCA3000_REG_ADDR_MODE,
					(rx[1] | SCA3000_FREE_FALL_DETECT));
	/* if on and should be off */
	else if (!val && (rx[1]&protect_mask))
		ret = sca3000_write_reg(st, SCA3000_REG_ADDR_MODE,
					(rx[1] & ~protect_mask));

	kfree(rx);
error_ret:
	mutex_unlock(&st->lock);

	return ret ? ret : len;
}