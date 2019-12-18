#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u64 ;
struct vxge_hw_ring_rxd_1 {int control_0; scalar_t__ host_control; } ;
struct __vxge_hw_channel {int dummy; } ;
struct __vxge_hw_ring {TYPE_2__* stats; int /*<<< orphan*/  cmpl_cnt; struct __vxge_hw_channel channel; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;
struct TYPE_3__ {scalar_t__ usage_cnt; scalar_t__ usage_max; } ;
struct TYPE_4__ {TYPE_1__ common_stats; } ;

/* Variables and functions */
 int VXGE_HW_INF_NO_MORE_COMPLETED_DESCRIPTORS ; 
 int VXGE_HW_OK ; 
 int VXGE_HW_RING_RXD_LIST_OWN_ADAPTER ; 
 scalar_t__ VXGE_HW_RING_RXD_T_CODE_GET (int) ; 
 scalar_t__ VXGE_HW_RING_RXD_T_CODE_UNUSED ; 
 scalar_t__ VXGE_HW_RING_T_CODE_FRM_DROP ; 
 int /*<<< orphan*/  vxge_assert (int) ; 
 int /*<<< orphan*/  vxge_hw_channel_dtr_complete (struct __vxge_hw_channel*) ; 
 int /*<<< orphan*/  vxge_hw_channel_dtr_try_complete (struct __vxge_hw_channel*,void**) ; 

enum vxge_hw_status vxge_hw_ring_rxd_next_completed(
	struct __vxge_hw_ring *ring, void **rxdh, u8 *t_code)
{
	struct __vxge_hw_channel *channel;
	struct vxge_hw_ring_rxd_1 *rxdp;
	enum vxge_hw_status status = VXGE_HW_OK;
	u64 control_0, own;

	channel = &ring->channel;

	vxge_hw_channel_dtr_try_complete(channel, rxdh);

	rxdp = (struct vxge_hw_ring_rxd_1 *)*rxdh;
	if (rxdp == NULL) {
		status = VXGE_HW_INF_NO_MORE_COMPLETED_DESCRIPTORS;
		goto exit;
	}

	control_0 = rxdp->control_0;
	own = control_0 & VXGE_HW_RING_RXD_LIST_OWN_ADAPTER;
	*t_code	= (u8)VXGE_HW_RING_RXD_T_CODE_GET(control_0);

	/* check whether it is not the end */
	if (!own || ((*t_code == VXGE_HW_RING_T_CODE_FRM_DROP) && own)) {

		vxge_assert(((struct vxge_hw_ring_rxd_1 *)rxdp)->host_control !=
				0);

		++ring->cmpl_cnt;
		vxge_hw_channel_dtr_complete(channel);

		vxge_assert(*t_code != VXGE_HW_RING_RXD_T_CODE_UNUSED);

		ring->stats->common_stats.usage_cnt++;
		if (ring->stats->common_stats.usage_max <
				ring->stats->common_stats.usage_cnt)
			ring->stats->common_stats.usage_max =
				ring->stats->common_stats.usage_cnt;

		status = VXGE_HW_OK;
		goto exit;
	}

	/* reset it. since we don't want to return
	 * garbage to the driver */
	*rxdh =	NULL;
	status = VXGE_HW_INF_NO_MORE_COMPLETED_DESCRIPTORS;
exit:
	return status;
}