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
struct hv_ring_buffer_info {TYPE_1__* ring_buffer; } ;
struct TYPE_2__ {scalar_t__ read_index; scalar_t__ interrupt_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static bool hv_need_to_signal(u32 old_write, struct hv_ring_buffer_info *rbi)
{
	mb();
	if (rbi->ring_buffer->interrupt_mask)
		return false;

	/* check interrupt_mask before read_index */
	rmb();
	/*
	 * This is the only case we need to signal when the
	 * ring transitions from being empty to non-empty.
	 */
	if (old_write == rbi->ring_buffer->read_index)
		return true;

	return false;
}