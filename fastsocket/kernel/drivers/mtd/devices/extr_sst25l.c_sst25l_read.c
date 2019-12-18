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
typedef  int /*<<< orphan*/  transfer ;
struct TYPE_2__ {size_t size; } ;
struct sst25l_flash {int /*<<< orphan*/  lock; int /*<<< orphan*/  spi; TYPE_1__ mtd; } ;
struct spi_transfer {unsigned char* tx_buf; int len; unsigned char* rx_buf; } ;
struct spi_message {int actual_length; } ;
struct mtd_info {int dummy; } ;
typedef  size_t loff_t ;
typedef  int /*<<< orphan*/  command ;

/* Variables and functions */
 int EINVAL ; 
 unsigned char SST25L_CMD_READ ; 
 int /*<<< orphan*/  memset (struct spi_transfer**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int /*<<< orphan*/  spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 
 int sst25l_wait_till_ready (struct sst25l_flash*) ; 
 struct sst25l_flash* to_sst25l_flash (struct mtd_info*) ; 

__attribute__((used)) static int sst25l_read(struct mtd_info *mtd, loff_t from, size_t len,
		       size_t *retlen, unsigned char *buf)
{
	struct sst25l_flash *flash = to_sst25l_flash(mtd);
	struct spi_transfer transfer[2];
	struct spi_message message;
	unsigned char command[4];
	int ret;

	/* Sanity checking */
	if (len == 0)
		return 0;

	if (from + len > flash->mtd.size)
		return -EINVAL;

	if (retlen)
		*retlen = 0;

	spi_message_init(&message);
	memset(&transfer, 0, sizeof(transfer));

	command[0] = SST25L_CMD_READ;
	command[1] = from >> 16;
	command[2] = from >> 8;
	command[3] = from;

	transfer[0].tx_buf = command;
	transfer[0].len = sizeof(command);
	spi_message_add_tail(&transfer[0], &message);

	transfer[1].rx_buf = buf;
	transfer[1].len = len;
	spi_message_add_tail(&transfer[1], &message);

	mutex_lock(&flash->lock);

	/* Wait for previous write/erase to complete */
	ret = sst25l_wait_till_ready(flash);
	if (ret) {
		mutex_unlock(&flash->lock);
		return ret;
	}

	spi_sync(flash->spi, &message);

	if (retlen && message.actual_length > sizeof(command))
		*retlen += message.actual_length - sizeof(command);

	mutex_unlock(&flash->lock);
	return 0;
}