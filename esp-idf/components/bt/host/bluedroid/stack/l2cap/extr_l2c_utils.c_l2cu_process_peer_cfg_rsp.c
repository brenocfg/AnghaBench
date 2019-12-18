#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int max_held_acks; } ;
struct TYPE_14__ {int tx_win_sz; } ;
struct TYPE_15__ {TYPE_4__ fcr; int /*<<< orphan*/  qos; scalar_t__ qos_present; } ;
struct TYPE_11__ {int /*<<< orphan*/  mon_tout; int /*<<< orphan*/  rtrans_tout; } ;
struct TYPE_12__ {TYPE_1__ fcr; } ;
struct TYPE_17__ {TYPE_6__ fcrb; TYPE_5__ our_cfg; TYPE_2__ peer_cfg; } ;
typedef  TYPE_7__ tL2C_CCB ;
struct TYPE_13__ {scalar_t__ mode; int tx_win_sz; int /*<<< orphan*/  mon_tout; int /*<<< orphan*/  rtrans_tout; } ;
struct TYPE_18__ {TYPE_3__ fcr; scalar_t__ fcr_present; int /*<<< orphan*/  qos; scalar_t__ qos_present; } ;
typedef  TYPE_8__ tL2CAP_CFG_INFO ;

/* Variables and functions */
 scalar_t__ L2CAP_FCR_ERTM_MODE ; 
 int /*<<< orphan*/  L2CAP_TRACE_DEBUG (char*,int,int,int) ; 

void l2cu_process_peer_cfg_rsp (tL2C_CCB *p_ccb, tL2CAP_CFG_INFO *p_cfg)
{
    /* If we wanted QoS and the peer sends us a positive response with QoS, use his values */
    if ( (p_cfg->qos_present) && (p_ccb->our_cfg.qos_present) ) {
        p_ccb->our_cfg.qos = p_cfg->qos;
    }

    if (p_cfg->fcr_present) {
        /* Save the retransmission and monitor timeout values */
        if (p_cfg->fcr.mode == L2CAP_FCR_ERTM_MODE) {
            p_ccb->peer_cfg.fcr.rtrans_tout = p_cfg->fcr.rtrans_tout;
            p_ccb->peer_cfg.fcr.mon_tout = p_cfg->fcr.mon_tout;
        }

        /* Calculate the max number of packets for which we can delay sending an ack */
        if (p_cfg->fcr.tx_win_sz < p_ccb->our_cfg.fcr.tx_win_sz) {
            p_ccb->fcrb.max_held_acks = p_cfg->fcr.tx_win_sz / 3;
        } else {
            p_ccb->fcrb.max_held_acks = p_ccb->our_cfg.fcr.tx_win_sz / 3;
        }

        L2CAP_TRACE_DEBUG ("l2cu_process_peer_cfg_rsp(): peer tx_win_sz: %d, our tx_win_sz: %d, max_held_acks: %d",
                           p_cfg->fcr.tx_win_sz, p_ccb->our_cfg.fcr.tx_win_sz, p_ccb->fcrb.max_held_acks);
    }
}