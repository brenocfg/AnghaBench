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
struct dmasg {unsigned long start_addr; unsigned int cfg; unsigned int x_count; size_t x_modify; unsigned int y_count; size_t y_modify; struct dmasg* next_desc_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,struct dmasg*,struct dmasg*,struct dmasg*,struct dmasg*,unsigned int,unsigned int,unsigned long,unsigned int) ; 

__attribute__((used)) static void setup_desc(struct dmasg *desc, void *buf, int fragcount,
		size_t fragsize, unsigned int cfg,
		unsigned int x_count, unsigned int ycount, size_t wdsize)
{

	int i;

	for (i = 0; i < fragcount; ++i) {
		desc[i].next_desc_addr  = &(desc[i + 1]);
		desc[i].start_addr = (unsigned long)buf + i*fragsize;
		desc[i].cfg = cfg;
		desc[i].x_count = x_count;
		desc[i].x_modify = wdsize;
		desc[i].y_count = ycount;
		desc[i].y_modify = wdsize;
	}

	/* make circular */
	desc[fragcount-1].next_desc_addr = desc;

	pr_debug("setup desc: desc0=%p, next0=%p, desc1=%p,"
		"next1=%p\nx_count=%x,y_count=%x,addr=0x%lx,cfs=0x%x\n",
		desc, desc[0].next_desc_addr,
		desc+1, desc[1].next_desc_addr,
		desc[0].x_count, desc[0].y_count,
		desc[0].start_addr, desc[0].cfg);
}