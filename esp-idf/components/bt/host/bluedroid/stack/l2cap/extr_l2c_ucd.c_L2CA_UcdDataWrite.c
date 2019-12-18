#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ state; } ;
struct TYPE_15__ {TYPE_1__ ucd; } ;
typedef  TYPE_2__ tL2C_RCB ;
struct TYPE_16__ {scalar_t__ ucd_mtu; int /*<<< orphan*/  ucd_out_sec_pending_q; int /*<<< orphan*/  handle; } ;
typedef  TYPE_3__ tL2C_LCB ;
struct TYPE_17__ {scalar_t__ cong_sent; int /*<<< orphan*/  buff_quota; int /*<<< orphan*/  xmit_hold_q; } ;
typedef  TYPE_4__ tL2C_CCB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_18__ {scalar_t__ offset; scalar_t__ len; int /*<<< orphan*/  layer_specific; } ;
typedef  TYPE_5__ BT_HDR ;
typedef  int* BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  L2CAP_CONNECTIONLESS_CID ; 
 int /*<<< orphan*/  L2CAP_DW_CONGESTED ; 
 int /*<<< orphan*/  L2CAP_DW_FAILED ; 
 int /*<<< orphan*/  L2CAP_DW_SUCCESS ; 
 int /*<<< orphan*/  L2CAP_TRACE_API (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  L2CAP_TRACE_ERROR (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ L2CAP_UCD_OVERHEAD ; 
 int /*<<< orphan*/  L2CEVT_L2CA_DATA_WRITE ; 
 scalar_t__ L2C_UCD_STATE_UNUSED ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fixed_queue_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c_csm_execute (TYPE_4__*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ l2c_ucd_connect (int*) ; 
 TYPE_4__* l2cu_find_ccb_by_cid (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* l2cu_find_lcb_by_bd_addr (int*,int /*<<< orphan*/ ) ; 
 TYPE_2__* l2cu_find_rcb_by_psm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free (TYPE_5__*) ; 

UINT16 L2CA_UcdDataWrite (UINT16 psm, BD_ADDR rem_bda, BT_HDR *p_buf, UINT16 flags)
{
    tL2C_LCB        *p_lcb;
    tL2C_CCB        *p_ccb;
    tL2C_RCB        *p_rcb;
    UINT8           *p;

    L2CAP_TRACE_API ("L2CA_UcdDataWrite()  PSM: 0x%04x  BDA: %08x%04x", psm,
                     (rem_bda[0] << 24) + (rem_bda[1] << 16) + (rem_bda[2] << 8) + rem_bda[3],
                     (rem_bda[4] << 8) + rem_bda[5]);

    /* Fail if the PSM is not registered */
    if (((p_rcb = l2cu_find_rcb_by_psm (psm)) == NULL)
            || ( p_rcb->ucd.state == L2C_UCD_STATE_UNUSED )) {
        L2CAP_TRACE_WARNING ("L2CAP - no RCB for L2CA_UcdDataWrite, PSM: 0x%04x", psm);
        osi_free (p_buf);
        return (L2CAP_DW_FAILED);
    }

    /* First, see if we already have a link to the remote */
    /*  then find the channel control block for UCD */
    if (((p_lcb = l2cu_find_lcb_by_bd_addr (rem_bda, BT_TRANSPORT_BR_EDR)) == NULL)
            || ((p_ccb = l2cu_find_ccb_by_cid (p_lcb, L2CAP_CONNECTIONLESS_CID)) == NULL)) {
        if ( l2c_ucd_connect (rem_bda) == FALSE ) {
            osi_free (p_buf);
            return (L2CAP_DW_FAILED);
        }

        /* If we still don't have lcb and ccb after connect attempt, then can't proceed */
        if (((p_lcb = l2cu_find_lcb_by_bd_addr (rem_bda, BT_TRANSPORT_BR_EDR)) == NULL)
                || ((p_ccb = l2cu_find_ccb_by_cid (p_lcb, L2CAP_CONNECTIONLESS_CID)) == NULL)) {
            osi_free (p_buf);
            return (L2CAP_DW_FAILED);
        }
    }

    /* write PSM */
    p_buf->offset -= L2CAP_UCD_OVERHEAD;
    p_buf->len += L2CAP_UCD_OVERHEAD;
    p = (UINT8 *)(p_buf + 1) + p_buf->offset;

    UINT16_TO_STREAM (p, psm);

    /* UCD MTU check */
    if ((p_lcb->ucd_mtu) && (p_buf->len > p_lcb->ucd_mtu)) {
        L2CAP_TRACE_WARNING ("L2CAP - Handle: 0x%04x  UCD bigger than peer's UCD mtu size cannot be sent", p_lcb->handle);
        osi_free (p_buf);
        return (L2CAP_DW_FAILED);
    }

    /* If already congested, do not accept any more packets */
    if (p_ccb->cong_sent) {
        L2CAP_TRACE_ERROR ("L2CAP - Handle: 0x%04x UCD cannot be sent, already congested count: %u  buff_quota: %u",
                           p_lcb->handle,
                           (fixed_queue_length(p_ccb->xmit_hold_q) +
                            fixed_queue_length(p_lcb->ucd_out_sec_pending_q)),
                           p_ccb->buff_quota);

        osi_free (p_buf);
        return (L2CAP_DW_FAILED);
    }

    /* channel based, packet based flushable or non-flushable */
    p_buf->layer_specific = flags;

    l2c_csm_execute (p_ccb, L2CEVT_L2CA_DATA_WRITE, p_buf);

    if (p_ccb->cong_sent) {
        return (L2CAP_DW_CONGESTED);
    } else {
        return (L2CAP_DW_SUCCESS);
    }
}