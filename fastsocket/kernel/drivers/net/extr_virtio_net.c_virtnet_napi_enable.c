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
struct virtnet_info {int /*<<< orphan*/  napi; int /*<<< orphan*/  rvq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtqueue_disable_cb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void virtnet_napi_enable(struct virtnet_info *vi)
{
	napi_enable(&vi->napi);

	/* If all buffers were filled by other side before we napi_enabled, we
	 * won't get another interrupt, so process any outstanding packets
	 * now.  virtnet_poll wants re-enable the queue, so we disable here.
	 * We synchronize against interrupts via NAPI_STATE_SCHED */
	if (napi_schedule_prep(&vi->napi)) {
		virtqueue_disable_cb(vi->rvq);
		local_bh_disable();
		__napi_schedule(&vi->napi);
		local_bh_enable();
	}
}