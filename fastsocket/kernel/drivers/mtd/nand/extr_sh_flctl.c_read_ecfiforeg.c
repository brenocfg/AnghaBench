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
typedef  int /*<<< orphan*/  uint8_t ;
struct sh_flctl {int dummy; } ;

/* Variables and functions */
 scalar_t__ FLECFIFO (struct sh_flctl*) ; 
 unsigned long be32_to_cpu (unsigned long) ; 
 unsigned long readl (void*) ; 
 scalar_t__ wait_recfifo_ready (struct sh_flctl*,int) ; 

__attribute__((used)) static int read_ecfiforeg(struct sh_flctl *flctl, uint8_t *buff, int sector)
{
	int i;
	unsigned long *ecc_buf = (unsigned long *)buff;
	void *fifo_addr = (void *)FLECFIFO(flctl);

	for (i = 0; i < 4; i++) {
		if (wait_recfifo_ready(flctl , sector))
			return 1;
		ecc_buf[i] = readl(fifo_addr);
		ecc_buf[i] = be32_to_cpu(ecc_buf[i]);
	}

	return 0;
}