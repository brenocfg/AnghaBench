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
struct jmb38x_ms_host {int io_pos; unsigned char* io_word; scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ DATA ; 
 scalar_t__ STATUS ; 
 int STATUS_FIFO_FULL ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned char,scalar_t__) ; 

__attribute__((used)) static unsigned int jmb38x_ms_write_data(struct jmb38x_ms_host *host,
					 unsigned char *buf,
					 unsigned int length)
{
	unsigned int off = 0;

	if (host->io_pos) {
		while (host->io_pos < 4 && length) {
			host->io_word[0] |=  buf[off++] << (host->io_pos * 8);
			host->io_pos++;
			length--;
		}
	}

	if (host->io_pos == 4
	    && !(STATUS_FIFO_FULL & readl(host->addr + STATUS))) {
		writel(host->io_word[0], host->addr + DATA);
		host->io_pos = 0;
		host->io_word[0] = 0;
	} else if (host->io_pos) {
		return off;
	}

	if (!length)
		return off;

	while (!(STATUS_FIFO_FULL & readl(host->addr + STATUS))) {
		if (length < 4)
			break;

		__raw_writel(*(unsigned int *)(buf + off),
			     host->addr + DATA);
		length -= 4;
		off += 4;
	}

	switch (length) {
	case 3:
		host->io_word[0] |= buf[off + 2] << 16;
		host->io_pos++;
	case 2:
		host->io_word[0] |= buf[off + 1] << 8;
		host->io_pos++;
	case 1:
		host->io_word[0] |= buf[off];
		host->io_pos++;
	}

	off += host->io_pos;

	return off;
}