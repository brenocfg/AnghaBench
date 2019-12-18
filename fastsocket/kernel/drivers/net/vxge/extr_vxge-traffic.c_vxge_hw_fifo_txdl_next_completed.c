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
typedef  int u8 ;
struct vxge_hw_fifo_txd {int control_0; scalar_t__ host_control; } ;
struct __vxge_hw_channel {int dummy; } ;
struct __vxge_hw_fifo {TYPE_2__* stats; struct __vxge_hw_channel channel; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;
typedef  enum vxge_hw_fifo_tcode { ____Placeholder_vxge_hw_fifo_tcode } vxge_hw_fifo_tcode ;
struct TYPE_3__ {scalar_t__ usage_cnt; } ;
struct TYPE_4__ {TYPE_1__ common_stats; } ;

/* Variables and functions */
 int VXGE_HW_FIFO_TXD_LIST_OWN_ADAPTER ; 
 scalar_t__ VXGE_HW_FIFO_TXD_T_CODE_GET (int) ; 
 int VXGE_HW_INF_NO_MORE_COMPLETED_DESCRIPTORS ; 
 int VXGE_HW_OK ; 
 int /*<<< orphan*/  vxge_assert (int) ; 
 int /*<<< orphan*/  vxge_hw_channel_dtr_complete (struct __vxge_hw_channel*) ; 
 int /*<<< orphan*/  vxge_hw_channel_dtr_try_complete (struct __vxge_hw_channel*,void**) ; 

enum vxge_hw_status vxge_hw_fifo_txdl_next_completed(
	struct __vxge_hw_fifo *fifo, void **txdlh,
	enum vxge_hw_fifo_tcode *t_code)
{
	struct __vxge_hw_channel *channel;
	struct vxge_hw_fifo_txd *txdp;
	enum vxge_hw_status status = VXGE_HW_OK;

	channel = &fifo->channel;

	vxge_hw_channel_dtr_try_complete(channel, txdlh);

	txdp = (struct vxge_hw_fifo_txd *)*txdlh;
	if (txdp == NULL) {
		status = VXGE_HW_INF_NO_MORE_COMPLETED_DESCRIPTORS;
		goto exit;
	}

	/* check whether host owns it */
	if (!(txdp->control_0 & VXGE_HW_FIFO_TXD_LIST_OWN_ADAPTER)) {

		vxge_assert(txdp->host_control != 0);

		vxge_hw_channel_dtr_complete(channel);

		*t_code = (u8)VXGE_HW_FIFO_TXD_T_CODE_GET(txdp->control_0);

		if (fifo->stats->common_stats.usage_cnt > 0)
			fifo->stats->common_stats.usage_cnt--;

		status = VXGE_HW_OK;
		goto exit;
	}

	/* no more completions */
	*txdlh = NULL;
	status = VXGE_HW_INF_NO_MORE_COMPLETED_DESCRIPTORS;
exit:
	return status;
}