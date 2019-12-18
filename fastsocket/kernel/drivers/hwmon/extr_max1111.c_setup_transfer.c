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
struct spi_transfer {int len; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct spi_message {int dummy; } ;
struct max1111_data {int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; struct spi_transfer* xfer; struct spi_message msg; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX1111_RX_BUF_SIZE ; 
 int /*<<< orphan*/  MAX1111_TX_BUF_SIZE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 

__attribute__((used)) static int setup_transfer(struct max1111_data *data)
{
	struct spi_message *m;
	struct spi_transfer *x;

	data->tx_buf = kmalloc(MAX1111_TX_BUF_SIZE, GFP_KERNEL);
	if (!data->tx_buf)
		return -ENOMEM;

	data->rx_buf = kmalloc(MAX1111_RX_BUF_SIZE, GFP_KERNEL);
	if (!data->rx_buf) {
		kfree(data->tx_buf);
		return -ENOMEM;
	}

	m = &data->msg;
	x = &data->xfer[0];

	spi_message_init(m);

	x->tx_buf = &data->tx_buf[0];
	x->len = 1;
	spi_message_add_tail(x, m);

	x++;
	x->rx_buf = &data->rx_buf[0];
	x->len = 2;
	spi_message_add_tail(x, m);

	return 0;
}