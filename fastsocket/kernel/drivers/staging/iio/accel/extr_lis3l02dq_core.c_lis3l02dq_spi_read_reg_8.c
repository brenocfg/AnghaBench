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
typedef  int /*<<< orphan*/  u8 ;
struct spi_transfer {int bits_per_word; int len; int cs_change; int /*<<< orphan*/ * rx_buf; scalar_t__* tx_buf; } ;
struct spi_message {int dummy; } ;
struct lis3l02dq_state {int /*<<< orphan*/  buf_lock; int /*<<< orphan*/ * rx; int /*<<< orphan*/  us; scalar_t__* tx; } ;
struct iio_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ LIS3L02DQ_READ_REG (int /*<<< orphan*/ ) ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 struct lis3l02dq_state* iio_dev_get_devdata (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

int lis3l02dq_spi_read_reg_8(struct device *dev, u8 reg_address, u8 *val)
{
	int ret;
	struct spi_message msg;
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct lis3l02dq_state *st = iio_dev_get_devdata(indio_dev);
	struct spi_transfer xfer = {
		.tx_buf = st->tx,
		.rx_buf = st->rx,
		.bits_per_word = 8,
		.len = 2,
		.cs_change = 1,
	};

	mutex_lock(&st->buf_lock);
	st->tx[0] = LIS3L02DQ_READ_REG(reg_address);
	st->tx[1] = 0;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(st->us, &msg);
	*val = st->rx[1];
	mutex_unlock(&st->buf_lock);

	return ret;
}