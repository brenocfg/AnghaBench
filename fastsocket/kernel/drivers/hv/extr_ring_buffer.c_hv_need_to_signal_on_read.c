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
typedef  scalar_t__ u32 ;
struct hv_ring_buffer_info {scalar_t__ ring_datasize; TYPE_1__* ring_buffer; } ;
struct TYPE_2__ {scalar_t__ write_index; scalar_t__ read_index; scalar_t__ pending_send_sz; } ;

/* Variables and functions */

__attribute__((used)) static bool hv_need_to_signal_on_read(u32 old_rd,
					 struct hv_ring_buffer_info *rbi)
{
	u32 prev_write_sz;
	u32 cur_write_sz;
	u32 r_size;
	u32 write_loc = rbi->ring_buffer->write_index;
	u32 read_loc = rbi->ring_buffer->read_index;
	u32 pending_sz = rbi->ring_buffer->pending_send_sz;

	/*
	 * If the other end is not blocked on write don't bother.
	 */
	if (pending_sz == 0)
		return false;

	r_size = rbi->ring_datasize;
	cur_write_sz = write_loc >= read_loc ? r_size - (write_loc - read_loc) :
			read_loc - write_loc;

	prev_write_sz = write_loc >= old_rd ? r_size - (write_loc - old_rd) :
			old_rd - write_loc;


	if ((prev_write_sz < pending_sz) && (cur_write_sz >= pending_sz))
		return true;

	return false;
}