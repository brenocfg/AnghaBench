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
struct jmb38x_ms_host {int io_pos; int* io_word; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int jmb38x_ms_write_reg_data(struct jmb38x_ms_host *host,
					     unsigned char *buf,
					     unsigned int length)
{
	unsigned int off = 0;

	while (host->io_pos < 4 && length) {
		host->io_word[0] &= ~(0xff << (host->io_pos * 8));
		host->io_word[0] |=  buf[off++] << (host->io_pos * 8);
		host->io_pos++;
		length--;
	}

	if (!length)
		return off;

	while (host->io_pos < 8 && length) {
		host->io_word[1] &= ~(0xff << (host->io_pos * 8));
		host->io_word[1] |=  buf[off++] << (host->io_pos * 8);
		host->io_pos++;
		length--;
	}

	return off;
}