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
struct spi_transfer {int bits_per_word; int len; int cs_change; int* tx_buf; int* rx_buf; } ;
struct spi_message {int dummy; } ;
struct kxsd9_state {int* tx; int* rx; int /*<<< orphan*/  buf_lock; int /*<<< orphan*/  us; } ;
struct iio_dev {struct kxsd9_state* dev_data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int KXSD9_FS_2 ; 
 int KXSD9_FS_4 ; 
 int KXSD9_FS_6 ; 
 int KXSD9_FS_8 ; 
 int KXSD9_FS_MASK ; 
 int KXSD9_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KXSD9_REG_CTRL_C ; 
 int KXSD9_WRITE (int /*<<< orphan*/ ) ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 
 int strict_strtol (char const*,int,long*) ; 

__attribute__((used)) static ssize_t kxsd9_write_accel_range(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf,
				      size_t len)
{
	long readin;
	struct spi_message msg;
	int ret;
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct kxsd9_state *st = indio_dev->dev_data;
	u8 val;
	struct spi_transfer xfers[] = {
		{
			.bits_per_word = 8,
			.len = 2,
			.cs_change = 1,
			.tx_buf = st->tx,
			.rx_buf = st->rx,
		}, {
			.bits_per_word = 8,
			.len = 2,
			.cs_change = 1,
			.tx_buf = st->tx,
		},
	};

	ret = strict_strtol(buf, 10, &readin);
	if (ret)
		return ret;
	switch (readin) {
	case 8:
		val = KXSD9_FS_8;
		break;
	case 6:
		val = KXSD9_FS_6;
		break;
	case 4:
		val = KXSD9_FS_4;
		break;
	case 2:
		val = KXSD9_FS_2;
		break;
	default:
		return -EINVAL;
	}
	mutex_lock(&st->buf_lock);
	st->tx[0] = KXSD9_READ(KXSD9_REG_CTRL_C);
	st->tx[1] = 0;
	spi_message_init(&msg);
	spi_message_add_tail(&xfers[0], &msg);
	ret = spi_sync(st->us, &msg);
	if (ret)
		goto error_ret;
	st->tx[0] = KXSD9_WRITE(KXSD9_REG_CTRL_C);
	st->tx[1] = (st->rx[1] & ~KXSD9_FS_MASK) | val;

	spi_message_init(&msg);
	spi_message_add_tail(&xfers[1], &msg);
	ret = spi_sync(st->us, &msg);
error_ret:
	mutex_unlock(&st->buf_lock);
	return ret ? ret : len;
}