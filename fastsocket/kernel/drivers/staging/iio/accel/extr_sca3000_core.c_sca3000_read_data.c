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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u8 ;
struct spi_transfer {int bits_per_word; int len; int cs_change; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct spi_message {int dummy; } ;
struct sca3000_state {TYPE_1__* us; int /*<<< orphan*/ * tx; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SCA3000_READ_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (TYPE_1__*,struct spi_message*) ; 

int sca3000_read_data(struct sca3000_state *st,
		      uint8_t reg_address_high,
		      u8 **rx_p,
		      int len)
{
	int ret;
	struct spi_message msg;
	struct spi_transfer xfer = {
		.bits_per_word = 8,
		.len = len + 1,
		.cs_change = 1,
		.tx_buf = st->tx,
	};

	*rx_p = kmalloc(len + 1, GFP_KERNEL);
	if (*rx_p == NULL) {
		ret = -ENOMEM;
		goto error_ret;
	}
	xfer.rx_buf = *rx_p;
	st->tx[0] = SCA3000_READ_REG(reg_address_high);
	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);

	ret = spi_sync(st->us, &msg);

	if (ret) {
		dev_err(get_device(&st->us->dev), "problem reading register");
		goto error_free_rx;
	}

	return 0;
error_free_rx:
	kfree(*rx_p);
error_ret:
	return ret;

}