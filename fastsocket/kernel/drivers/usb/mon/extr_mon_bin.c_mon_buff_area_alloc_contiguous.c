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
struct mon_reader_bin {scalar_t__ b_cnt; scalar_t__ b_size; unsigned int b_in; } ;

/* Variables and functions */
 unsigned int PKT_ALIGN ; 
 int /*<<< orphan*/  mon_buff_area_fill (struct mon_reader_bin*,unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned int mon_buff_area_alloc_contiguous(struct mon_reader_bin *rp,
    unsigned int size)
{
	unsigned int offset;
	unsigned int fill_size;

	size = (size + PKT_ALIGN-1) & ~(PKT_ALIGN-1);
	if (rp->b_cnt + size > rp->b_size)
		return ~0;
	if (rp->b_in + size > rp->b_size) {
		/*
		 * This would wrap. Find if we still have space after
		 * skipping to the end of the buffer. If we do, place
		 * a filler packet and allocate a new packet.
		 */
		fill_size = rp->b_size - rp->b_in;
		if (rp->b_cnt + size + fill_size > rp->b_size)
			return ~0;
		mon_buff_area_fill(rp, rp->b_in, fill_size);

		offset = 0;
		rp->b_in = size;
		rp->b_cnt += size + fill_size;
	} else if (rp->b_in + size == rp->b_size) {
		offset = rp->b_in;
		rp->b_in = 0;
		rp->b_cnt += size;
	} else {
		offset = rp->b_in;
		rp->b_in += size;
		rp->b_cnt += size;
	}
	return offset;
}