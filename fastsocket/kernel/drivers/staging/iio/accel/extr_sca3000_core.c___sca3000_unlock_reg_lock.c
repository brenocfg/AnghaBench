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
struct spi_transfer {int bits_per_word; int len; int cs_change; int* tx_buf; } ;
struct spi_message {int dummy; } ;
struct sca3000_state {int* tx; int /*<<< orphan*/  us; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCA3000_REG_ADDR_UNLOCK ; 
 void* SCA3000_WRITE_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static int __sca3000_unlock_reg_lock(struct sca3000_state *st)
{
	struct spi_message msg;
	struct spi_transfer xfer[3] = {
		{
			.bits_per_word = 8,
			.len = 2,
			.cs_change = 1,
			.tx_buf = st->tx,
		}, {
			.bits_per_word = 8,
			.len = 2,
			.cs_change = 1,
			.tx_buf = st->tx + 2,
		}, {
			.bits_per_word = 8,
			.len = 2,
			.cs_change = 1,
			.tx_buf = st->tx + 4,
		},
	};
	st->tx[0] = SCA3000_WRITE_REG(SCA3000_REG_ADDR_UNLOCK);
	st->tx[1] = 0x00;
	st->tx[2] = SCA3000_WRITE_REG(SCA3000_REG_ADDR_UNLOCK);
	st->tx[3] = 0x50;
	st->tx[4] = SCA3000_WRITE_REG(SCA3000_REG_ADDR_UNLOCK);
	st->tx[5] = 0xA0;
	spi_message_init(&msg);
	spi_message_add_tail(&xfer[0], &msg);
	spi_message_add_tail(&xfer[1], &msg);
	spi_message_add_tail(&xfer[2], &msg);

	return spi_sync(st->us, &msg);
}