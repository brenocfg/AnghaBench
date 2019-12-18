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
struct tifm_ms {int io_pos; unsigned char io_word; struct tifm_dev* dev; } ;
struct tifm_dev {scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ SOCK_MS_DATA ; 
 scalar_t__ SOCK_MS_STATUS ; 
 scalar_t__ SOCK_MS_SYSTEM ; 
 int TIFM_MS_STAT_FUL ; 
 int TIFM_MS_SYS_FDIR ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static unsigned int tifm_ms_write_data(struct tifm_ms *host,
				       unsigned char *buf, unsigned int length)
{
	struct tifm_dev *sock = host->dev;
	unsigned int off = 0;

	if (host->io_pos) {
		while (host->io_pos < 4 && length) {
			host->io_word |=  buf[off++] << (host->io_pos * 8);
			host->io_pos++;
			length--;
		}
	}

	if (host->io_pos == 4
	    && !(TIFM_MS_STAT_FUL & readl(sock->addr + SOCK_MS_STATUS))) {
		writel(TIFM_MS_SYS_FDIR | readl(sock->addr + SOCK_MS_SYSTEM),
		       sock->addr + SOCK_MS_SYSTEM);
		writel(host->io_word, sock->addr + SOCK_MS_DATA);
		host->io_pos = 0;
		host->io_word = 0;
	} else if (host->io_pos) {
		return off;
	}

	if (!length)
		return off;

	while (!(TIFM_MS_STAT_FUL & readl(sock->addr + SOCK_MS_STATUS))) {
		if (length < 4)
			break;
		writel(TIFM_MS_SYS_FDIR | readl(sock->addr + SOCK_MS_SYSTEM),
		       sock->addr + SOCK_MS_SYSTEM);
		__raw_writel(*(unsigned int *)(buf + off),
			     sock->addr + SOCK_MS_DATA);
		length -= 4;
		off += 4;
	}

	switch (length) {
	case 3:
		host->io_word |= buf[off + 2] << 16;
		host->io_pos++;
	case 2:
		host->io_word |= buf[off + 1] << 8;
		host->io_pos++;
	case 1:
		host->io_word |= buf[off];
		host->io_pos++;
	}

	off += host->io_pos;

	return off;
}