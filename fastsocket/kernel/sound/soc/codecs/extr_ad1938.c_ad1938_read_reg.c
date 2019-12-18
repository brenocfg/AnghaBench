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
struct spi_transfer {char* tx_buf; char* rx_buf; int len; } ;
struct spi_message {int dummy; } ;
struct snd_soc_codec {int /*<<< orphan*/  control_data; } ;

/* Variables and functions */
 int AD1938_SPI_ADDR ; 
 int AD1938_SPI_BUFLEN ; 
 int AD1938_SPI_READ ; 
 unsigned int EIO ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static unsigned int ad1938_read_reg(struct snd_soc_codec *codec,
						unsigned int reg)
{
	char w_buf[AD1938_SPI_BUFLEN];
	char r_buf[AD1938_SPI_BUFLEN];
	int ret;

	struct spi_transfer t = {
		.tx_buf = w_buf,
		.rx_buf = r_buf,
		.len = AD1938_SPI_BUFLEN,
	};
	struct spi_message m;

	w_buf[0] = (AD1938_SPI_ADDR << 1) | AD1938_SPI_READ;
	w_buf[1] = reg;
	w_buf[2] = 0;

	spi_message_init(&m);
	spi_message_add_tail(&t, &m);
	ret = spi_sync(codec->control_data, &m);
	if (ret == 0)
		return	r_buf[2];
	else
		return -EIO;
}