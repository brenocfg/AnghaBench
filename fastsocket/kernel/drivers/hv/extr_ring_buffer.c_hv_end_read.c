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
typedef  int /*<<< orphan*/  u32 ;
struct hv_ring_buffer_info {TYPE_1__* ring_buffer; } ;
struct TYPE_2__ {scalar_t__ interrupt_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  hv_get_ringbuffer_availbytes (struct hv_ring_buffer_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 

u32 hv_end_read(struct hv_ring_buffer_info *rbi)
{
	u32 read;
	u32 write;

	rbi->ring_buffer->interrupt_mask = 0;
	mb();

	/*
	 * Now check to see if the ring buffer is still empty.
	 * If it is not, we raced and we need to process new
	 * incoming messages.
	 */
	hv_get_ringbuffer_availbytes(rbi, &read, &write);

	return read;
}