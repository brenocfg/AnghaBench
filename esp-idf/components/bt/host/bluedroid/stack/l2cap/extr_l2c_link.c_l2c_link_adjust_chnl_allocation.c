#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mode; } ;
struct TYPE_7__ {TYPE_1__ fcr; } ;
struct TYPE_8__ {int tx_data_rate; int rx_data_rate; int buff_quota; int /*<<< orphan*/  ccb_priority; TYPE_2__ peer_cfg; int /*<<< orphan*/  local_cid; int /*<<< orphan*/  in_use; } ;
typedef  TYPE_3__ tL2C_CCB ;
typedef  int tL2CAP_CHNL_DATA_RATE ;
typedef  scalar_t__ UINT8 ;
struct TYPE_9__ {TYPE_3__* ccb_pool; } ;

/* Variables and functions */
 int L2CAP_CBB_DEFAULT_DATA_RATE_BUFF_QUOTA ; 
 int /*<<< orphan*/  L2CAP_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  L2CAP_TRACE_EVENT (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ MAX_L2CAP_CHANNELS ; 
 TYPE_5__ l2cb ; 
 int /*<<< orphan*/  l2cu_check_channel_congestion (TYPE_3__*) ; 

void l2c_link_adjust_chnl_allocation (void)
{
    UINT8       xx;


    L2CAP_TRACE_DEBUG ("l2c_link_adjust_chnl_allocation");

    /* assign buffer quota to each channel based on its data rate requirement */
    for (xx = 0; xx < MAX_L2CAP_CHANNELS; xx++)
    {
        tL2C_CCB *p_ccb = l2cb.ccb_pool + xx;

        if (!p_ccb->in_use) {
            continue;
		}

        tL2CAP_CHNL_DATA_RATE data_rate = p_ccb->tx_data_rate + p_ccb->rx_data_rate;
        p_ccb->buff_quota = L2CAP_CBB_DEFAULT_DATA_RATE_BUFF_QUOTA * data_rate;
        L2CAP_TRACE_EVENT("CID:0x%04x FCR Mode:%u Priority:%u TxDataRate:%u RxDataRate:%u Quota:%u",
                          p_ccb->local_cid, p_ccb->peer_cfg.fcr.mode,
                          p_ccb->ccb_priority, p_ccb->tx_data_rate,
                          p_ccb->rx_data_rate, p_ccb->buff_quota);

        /* quota may be change so check congestion */
        l2cu_check_channel_congestion (p_ccb);
    }
}