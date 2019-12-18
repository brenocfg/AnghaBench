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
typedef  int /*<<< orphan*/  tx_buf ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct sensor_device_attribute {int index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adcxx {int reference; int /*<<< orphan*/  lock; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  rx_buf ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 struct adcxx* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_write_then_read (struct spi_device*,int*,int,int*,int) ; 
 int sprintf (char*,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static ssize_t adcxx_read(struct device *dev,
		struct device_attribute *devattr, char *buf)
{
	struct spi_device *spi = to_spi_device(dev);
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct adcxx *adc = dev_get_drvdata(&spi->dev);
	u8 tx_buf[2] = { attr->index << 3 }; /* other bits are don't care */
	u8 rx_buf[2];
	int status;
	int value;

	if (mutex_lock_interruptible(&adc->lock))
		return -ERESTARTSYS;

	status = spi_write_then_read(spi, tx_buf, sizeof(tx_buf),
					rx_buf, sizeof(rx_buf));
	if (status < 0) {
		dev_warn(dev, "spi_write_then_read failed with status %d\n",
				status);
		goto out;
	}

	value = (rx_buf[0] << 8) + rx_buf[1];
	dev_dbg(dev, "raw value = 0x%x\n", value);

	value = value * adc->reference >> 12;
	status = sprintf(buf, "%d\n", value);
out:
	mutex_unlock(&adc->lock);
	return status;
}