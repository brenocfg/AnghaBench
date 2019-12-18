#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tsl2561_state {int /*<<< orphan*/  command_buf_lock; TYPE_1__* command_buf; int /*<<< orphan*/  client; } ;
struct iio_dev_attr {int /*<<< orphan*/  address; } ;
struct iio_dev {struct tsl2561_state* dev_data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int cmd; int word; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_word_data (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t tsl2561_read_val(struct device *dev,
				struct device_attribute *attr,
				char *buf)
{
	int ret = 0, data;
	ssize_t len = 0;
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct tsl2561_state *st = indio_dev->dev_data;

	mutex_lock(&st->command_buf_lock);
	st->command_buf->cmd = 1;
	st->command_buf->word = 1;
	st->command_buf->address = this_attr->address;

	data = i2c_smbus_read_word_data(st->client, *(char *)(st->command_buf));
	if (data < 0) {
		ret = data;
		goto error_ret;
	}
	len = sprintf(buf, "%u\n", data);

error_ret:
	mutex_unlock(&st->command_buf_lock);

	return ret ? ret : len;
}