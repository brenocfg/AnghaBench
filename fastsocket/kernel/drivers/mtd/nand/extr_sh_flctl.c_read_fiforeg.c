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
struct sh_flctl {int /*<<< orphan*/ * done_buff; } ;

/* Variables and functions */
 scalar_t__ FLDTFIFO (struct sh_flctl*) ; 
 unsigned long be32_to_cpu (unsigned long) ; 
 unsigned long readl (void*) ; 
 int /*<<< orphan*/  wait_rfifo_ready (struct sh_flctl*) ; 

__attribute__((used)) static void read_fiforeg(struct sh_flctl *flctl, int rlen, int offset)
{
	int i, len_4align;
	unsigned long *buf = (unsigned long *)&flctl->done_buff[offset];
	void *fifo_addr = (void *)FLDTFIFO(flctl);

	len_4align = (rlen + 3) / 4;

	for (i = 0; i < len_4align; i++) {
		wait_rfifo_ready(flctl);
		buf[i] = readl(fifo_addr);
		buf[i] = be32_to_cpu(buf[i]);
	}
}