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
struct tifm_ms {int io_pos; int io_word; struct tifm_dev* dev; } ;
struct tifm_dev {scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ SOCK_MS_DATA ; 
 scalar_t__ SOCK_MS_STATUS ; 
 int TIFM_MS_STAT_EMP ; 
 unsigned int __raw_readl (scalar_t__) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static unsigned int tifm_ms_read_data(struct tifm_ms *host,
				      unsigned char *buf, unsigned int length)
{
	struct tifm_dev *sock = host->dev;
	unsigned int off = 0;

	while (host->io_pos && length) {
		buf[off++] = host->io_word & 0xff;
		host->io_word >>= 8;
		length--;
		host->io_pos--;
	}

	if (!length)
		return off;

	while (!(TIFM_MS_STAT_EMP & readl(sock->addr + SOCK_MS_STATUS))) {
		if (length < 4)
			break;
		*(unsigned int *)(buf + off) = __raw_readl(sock->addr
							   + SOCK_MS_DATA);
		length -= 4;
		off += 4;
	}

	if (length
	    && !(TIFM_MS_STAT_EMP & readl(sock->addr + SOCK_MS_STATUS))) {
		host->io_word = readl(sock->addr + SOCK_MS_DATA);
		for (host->io_pos = 4; host->io_pos; --host->io_pos) {
			buf[off++] = host->io_word & 0xff;
			host->io_word >>= 8;
			length--;
			if (!length)
				break;
		}
	}

	return off;
}