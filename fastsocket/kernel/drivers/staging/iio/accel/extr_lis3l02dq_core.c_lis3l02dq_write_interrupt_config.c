#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct iio_event_attr {int mask; TYPE_2__* listel; } ;
struct iio_dev {int /*<<< orphan*/  mlock; TYPE_1__** interrupts; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_5__ {scalar_t__ refcount; } ;
struct TYPE_4__ {int /*<<< orphan*/  ev_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIS3L02DQ_REG_CTRL_2_ADDR ; 
 int LIS3L02DQ_REG_CTRL_2_ENABLE_INTERRUPT ; 
 int /*<<< orphan*/  LIS3L02DQ_REG_WAKE_UP_CFG_ADDR ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  iio_add_event_to_list (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_remove_event_from_list (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int lis3l02dq_spi_read_reg_8 (struct device*,int /*<<< orphan*/ ,int*) ; 
 int lis3l02dq_spi_write_reg_8 (struct device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct iio_event_attr* to_iio_event_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t lis3l02dq_write_interrupt_config(struct device *dev,
						struct device_attribute *attr,
						const char *buf,
						size_t len)
{
	struct iio_event_attr *this_attr = to_iio_event_attr(attr);
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	int ret, currentlyset, changed = 0;
	u8 valold, controlold;
	bool val;

	val = !(buf[0] == '0');

	mutex_lock(&indio_dev->mlock);
	/* read current value */
	ret = lis3l02dq_spi_read_reg_8(dev,
				       LIS3L02DQ_REG_WAKE_UP_CFG_ADDR,
				       &valold);
	if (ret)
		goto error_mutex_unlock;

	/* read current control */
	ret = lis3l02dq_spi_read_reg_8(dev,
				       LIS3L02DQ_REG_CTRL_2_ADDR,
				       &controlold);
	if (ret)
		goto error_mutex_unlock;
	currentlyset = !!(valold & this_attr->mask);
	if (val == false && currentlyset) {
		valold &= ~this_attr->mask;
		changed = 1;
		iio_remove_event_from_list(this_attr->listel,
						 &indio_dev->interrupts[0]
						 ->ev_list);
	} else if (val == true && !currentlyset) {
		changed = 1;
		valold |= this_attr->mask;
		iio_add_event_to_list(this_attr->listel,
					    &indio_dev->interrupts[0]->ev_list);
	}

	if (changed) {
		ret = lis3l02dq_spi_write_reg_8(dev,
						LIS3L02DQ_REG_WAKE_UP_CFG_ADDR,
						&valold);
		if (ret)
			goto error_mutex_unlock;
		/* This always enables the interrupt, even if we've remove the
		 * last thing using it. For this device we can use the reference
		 * count on the handler to tell us if anyone wants the interrupt
		 */
		controlold = this_attr->listel->refcount ?
			(controlold | LIS3L02DQ_REG_CTRL_2_ENABLE_INTERRUPT) :
			(controlold & ~LIS3L02DQ_REG_CTRL_2_ENABLE_INTERRUPT);
		ret = lis3l02dq_spi_write_reg_8(dev,
						LIS3L02DQ_REG_CTRL_2_ADDR,
						&controlold);
		if (ret)
			goto error_mutex_unlock;
	}
error_mutex_unlock:
	mutex_unlock(&indio_dev->mlock);

	return ret ? ret : len;
}