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
typedef  int uint8_t ;
struct spi_transfer {int len; int cs_change; int* tx_buf; } ;
struct spi_message {int dummy; } ;
struct corgi_lcd {int* buf; int /*<<< orphan*/  spi_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static int corgi_ssp_lcdtg_send(struct corgi_lcd *lcd, int adrs, uint8_t data)
{
	struct spi_message msg;
	struct spi_transfer xfer = {
		.len		= 1,
		.cs_change	= 1,
		.tx_buf		= lcd->buf,
	};

	lcd->buf[0] = ((adrs & 0x07) << 5) | (data & 0x1f);
	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);

	return spi_sync(lcd->spi_dev, &msg);
}