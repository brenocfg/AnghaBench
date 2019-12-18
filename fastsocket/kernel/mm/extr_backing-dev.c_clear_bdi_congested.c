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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct backing_dev_info {int /*<<< orphan*/  state; } ;
typedef  enum bdi_state { ____Placeholder_bdi_state } bdi_state ;

/* Variables and functions */
 int BDI_async_congested ; 
 int BDI_sync_congested ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * congestion_wqh ; 
 int /*<<< orphan*/ * nr_bdi_congested ; 
 int /*<<< orphan*/  smp_mb__after_clear_bit () ; 
 scalar_t__ test_and_clear_bit (int,int /*<<< orphan*/ *) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void clear_bdi_congested(struct backing_dev_info *bdi, int sync)
{
	enum bdi_state bit;
	wait_queue_head_t *wqh = &congestion_wqh[sync];

	bit = sync ? BDI_sync_congested : BDI_async_congested;
	if (test_and_clear_bit(bit, &bdi->state))
		atomic_dec(&nr_bdi_congested[sync]);
	smp_mb__after_clear_bit();
	if (waitqueue_active(wqh))
		wake_up(wqh);
}