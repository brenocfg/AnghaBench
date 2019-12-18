#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct spi_transfer {int len; char* rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct spi_message {int dummy; } ;
struct TYPE_3__ {unsigned int size; } ;
struct at25_data {int addrlen; int /*<<< orphan*/  lock; TYPE_2__* spi; TYPE_1__ bin; } ;
typedef  size_t ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT25_READ ; 
 int /*<<< orphan*/  EE_MAXADDRLEN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,size_t,unsigned int,int) ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 size_t spi_sync (TYPE_2__*,struct spi_message*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ssize_t
at25_ee_read(
	struct at25_data	*at25,
	char			*buf,
	unsigned		offset,
	size_t			count
)
{
	u8			command[EE_MAXADDRLEN + 1];
	u8			*cp;
	ssize_t			status;
	struct spi_transfer	t[2];
	struct spi_message	m;

	if (unlikely(offset >= at25->bin.size))
		return 0;
	if ((offset + count) > at25->bin.size)
		count = at25->bin.size - offset;
	if (unlikely(!count))
		return count;

	cp = command;
	*cp++ = AT25_READ;

	/* 8/16/24-bit address is written MSB first */
	switch (at25->addrlen) {
	default:	/* case 3 */
		*cp++ = offset >> 16;
	case 2:
		*cp++ = offset >> 8;
	case 1:
	case 0:	/* can't happen: for better codegen */
		*cp++ = offset >> 0;
	}

	spi_message_init(&m);
	memset(t, 0, sizeof t);

	t[0].tx_buf = command;
	t[0].len = at25->addrlen + 1;
	spi_message_add_tail(&t[0], &m);

	t[1].rx_buf = buf;
	t[1].len = count;
	spi_message_add_tail(&t[1], &m);

	mutex_lock(&at25->lock);

	/* Read it all at once.
	 *
	 * REVISIT that's potentially a problem with large chips, if
	 * other devices on the bus need to be accessed regularly or
	 * this chip is clocked very slowly
	 */
	status = spi_sync(at25->spi, &m);
	dev_dbg(&at25->spi->dev,
		"read %Zd bytes at %d --> %d\n",
		count, offset, (int) status);

	mutex_unlock(&at25->lock);
	return status ? status : count;
}