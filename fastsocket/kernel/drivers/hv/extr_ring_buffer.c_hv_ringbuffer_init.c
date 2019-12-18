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
typedef  void* u32 ;
struct hv_ring_buffer_info {int /*<<< orphan*/  ring_lock; void* ring_datasize; void* ring_size; struct hv_ring_buffer* ring_buffer; } ;
struct hv_ring_buffer {scalar_t__ write_index; scalar_t__ read_index; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  memset (struct hv_ring_buffer_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int hv_ringbuffer_init(struct hv_ring_buffer_info *ring_info,
		   void *buffer, u32 buflen)
{
	if (sizeof(struct hv_ring_buffer) != PAGE_SIZE)
		return -EINVAL;

	memset(ring_info, 0, sizeof(struct hv_ring_buffer_info));

	ring_info->ring_buffer = (struct hv_ring_buffer *)buffer;
	ring_info->ring_buffer->read_index =
		ring_info->ring_buffer->write_index = 0;

	ring_info->ring_size = buflen;
	ring_info->ring_datasize = buflen - sizeof(struct hv_ring_buffer);

	spin_lock_init(&ring_info->ring_lock);

	return 0;
}