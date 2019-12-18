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
struct spi_transfer {int bits_per_word; int len; int cs_change; int* rx_buf; scalar_t__* tx_buf; } ;
struct spi_message {int dummy; } ;
struct kxsd9_state {int* rx; int /*<<< orphan*/  buf_lock; int /*<<< orphan*/  us; scalar_t__* tx; } ;
struct iio_dev {struct kxsd9_state* dev_data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
#define  KXSD9_FS_2 131 
#define  KXSD9_FS_4 130 
#define  KXSD9_FS_6 129 
#define  KXSD9_FS_8 128 
 int KXSD9_FS_MASK ; 
 scalar_t__ KXSD9_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KXSD9_REG_CTRL_C ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 
 int sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t kxsd9_read_accel_range(struct device *dev,
				      struct device_attribute *attr,
				      char *buf)
{
	int ret;
	ssize_t len = 0;
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct kxsd9_state *st = indio_dev->dev_data;
	struct spi_transfer xfer = {
		.bits_per_word = 8,
		.len = 2,
		.cs_change = 1,
		.tx_buf = st->tx,
		.rx_buf = st->rx,
	};
	struct spi_message msg;

	mutex_lock(&st->buf_lock);
	st->tx[0] = KXSD9_READ(KXSD9_REG_CTRL_C);
	st->tx[1] = 0;
	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(st->us, &msg);
	if (ret)
		goto error_ret;

	switch (st->rx[1] & KXSD9_FS_MASK) {
	case KXSD9_FS_8:
		len += sprintf(buf, "8\n");
		break;
	case KXSD9_FS_6:
		len += sprintf(buf, "6\n");
		break;
	case KXSD9_FS_4:
		len += sprintf(buf, "4\n");
		break;
	case KXSD9_FS_2:
		len += sprintf(buf, "2\n");
		break;
	}

error_ret:
	mutex_unlock(&st->buf_lock);

	return ret ? ret : len;
}