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
typedef  scalar_t__ u8 ;
struct spi_transfer {int* tx_buf; int bits_per_word; int len; int cs_change; } ;
struct spi_message {int dummy; } ;
struct lis3l02dq_state {int* tx; int /*<<< orphan*/  buf_lock; int /*<<< orphan*/  us; } ;
struct iio_dev {int dummy; } ;
struct device {int dummy; } ;
typedef  int s16 ;

/* Variables and functions */
 void* LIS3L02DQ_WRITE_REG (scalar_t__) ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 struct lis3l02dq_state* iio_dev_get_devdata (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static int lis3l02dq_spi_write_reg_s16(struct device *dev,
				       u8 lower_reg_address,
				       s16 value)
{
	int ret;
	struct spi_message msg;
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct lis3l02dq_state *st = iio_dev_get_devdata(indio_dev);
	struct spi_transfer xfers[] = { {
			.tx_buf = st->tx,
			.bits_per_word = 8,
			.len = 2,
			.cs_change = 1,
		}, {
			.tx_buf = st->tx + 2,
			.bits_per_word = 8,
			.len = 2,
			.cs_change = 1,
		},
	};

	mutex_lock(&st->buf_lock);
	st->tx[0] = LIS3L02DQ_WRITE_REG(lower_reg_address);
	st->tx[1] = value & 0xFF;
	st->tx[2] = LIS3L02DQ_WRITE_REG(lower_reg_address + 1);
	st->tx[3] = (value >> 8) & 0xFF;

	spi_message_init(&msg);
	spi_message_add_tail(&xfers[0], &msg);
	spi_message_add_tail(&xfers[1], &msg);
	ret = spi_sync(st->us, &msg);
	mutex_unlock(&st->buf_lock);

	return ret;
}