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
typedef  int u32 ;
typedef  int /*<<< orphan*/  t ;
struct wl12xx_spi_glue {int /*<<< orphan*/  dev; } ;
struct wl1271 {int* buffer_busyword; } ;
struct spi_transfer {int* rx_buf; int len; int cs_change; } ;
struct spi_message {int dummy; } ;
struct device {struct device* parent; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int WL1271_BUSY_WORD_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int /*<<< orphan*/  spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 
 int /*<<< orphan*/  to_spi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wl12xx_spi_read_busy(struct device *child)
{
	struct wl12xx_spi_glue *glue = dev_get_drvdata(child->parent);
	struct wl1271 *wl = dev_get_drvdata(child);
	struct spi_transfer t[1];
	struct spi_message m;
	u32 *busy_buf;
	int num_busy_bytes = 0;

	/*
	 * Read further busy words from SPI until a non-busy word is
	 * encountered, then read the data itself into the buffer.
	 */

	num_busy_bytes = WL1271_BUSY_WORD_TIMEOUT;
	busy_buf = wl->buffer_busyword;
	while (num_busy_bytes) {
		num_busy_bytes--;
		spi_message_init(&m);
		memset(t, 0, sizeof(t));
		t[0].rx_buf = busy_buf;
		t[0].len = sizeof(u32);
		t[0].cs_change = true;
		spi_message_add_tail(&t[0], &m);
		spi_sync(to_spi_device(glue->dev), &m);

		if (*busy_buf & 0x1)
			return 0;
	}

	/* The SPI bus is unresponsive, the read failed. */
	dev_err(child->parent, "SPI read busy-word timeout!\n");
	return -ETIMEDOUT;
}