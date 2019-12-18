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
struct sca3000_state {int /*<<< orphan*/  lock; int /*<<< orphan*/  info; } ;
struct iio_dev {struct sca3000_state* dev_data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCA3000_REG_CTRL_SEL_OUT_CTRL ; 
 int __sca3000_get_base_freq (struct sca3000_state*,int /*<<< orphan*/ ,int*) ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sca3000_read_ctrl_reg (struct sca3000_state*,int /*<<< orphan*/ ,int**) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t sca3000_read_frequency(struct device *dev,
			       struct device_attribute *attr,
			       char *buf)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct sca3000_state *st = indio_dev->dev_data;
	int ret, len = 0, base_freq = 0;
	u8 *rx;
	mutex_lock(&st->lock);
	ret = __sca3000_get_base_freq(st, st->info, &base_freq);
	if (ret)
		goto error_ret_mut;
	ret = sca3000_read_ctrl_reg(st, SCA3000_REG_CTRL_SEL_OUT_CTRL, &rx);
	mutex_unlock(&st->lock);
	if (ret)
		goto error_ret;
	if (base_freq > 0)
		switch (rx[1]&0x03) {
		case 0x00:
		case 0x03:
			len = sprintf(buf, "%d\n", base_freq);
			break;
		case 0x01:
			len = sprintf(buf, "%d\n", base_freq/2);
			break;
		case 0x02:
			len = sprintf(buf, "%d\n", base_freq/4);
			break;
	};
			kfree(rx);
	return len;
error_ret_mut:
	mutex_unlock(&st->lock);
error_ret:
	return ret;
}