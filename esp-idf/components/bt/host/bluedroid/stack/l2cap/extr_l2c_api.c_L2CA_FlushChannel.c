#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  link_xmit_data_q; int /*<<< orphan*/  handle; } ;
typedef  TYPE_5__ tL2C_LCB ;
struct TYPE_14__ {scalar_t__ mode; } ;
struct TYPE_15__ {TYPE_1__ fcr; } ;
struct TYPE_19__ {int /*<<< orphan*/  xmit_hold_q; int /*<<< orphan*/  local_cid; TYPE_4__* p_rcb; TYPE_2__ peer_cfg; TYPE_5__* p_lcb; } ;
typedef  TYPE_6__ tL2C_CCB ;
typedef  int /*<<< orphan*/  list_node_t ;
typedef  scalar_t__ UINT16 ;
struct TYPE_20__ {scalar_t__ layer_specific; scalar_t__ event; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* pL2CA_TxComplete_Cb ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_17__ {TYPE_3__ api; } ;
struct TYPE_13__ {scalar_t__ is_flush_active; } ;
typedef  TYPE_7__ BT_HDR ;

/* Variables and functions */
 scalar_t__ BTM_GetNumScoLinks () ; 
 int /*<<< orphan*/  BTM_ReadLocalFeatures () ; 
 scalar_t__ FALSE ; 
 scalar_t__ HCI_NON_FLUSHABLE_PB_SUPPORTED (int /*<<< orphan*/ ) ; 
 scalar_t__ L2CAP_FCR_ERTM_MODE ; 
 scalar_t__ L2CAP_FLUSH_CHANS_GET ; 
 int /*<<< orphan*/  L2CAP_TRACE_API (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  L2CAP_TRACE_DEBUG (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*,scalar_t__) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  btsnd_hcic_enhanced_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fixed_queue_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixed_queue_is_empty (int /*<<< orphan*/ ) ; 
 scalar_t__ fixed_queue_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixed_queue_try_peek_first (int /*<<< orphan*/ ) ; 
 TYPE_12__ l2cb ; 
 int /*<<< orphan*/  l2cu_check_channel_congestion (TYPE_6__*) ; 
 TYPE_6__* l2cu_find_ccb_by_cid (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * list_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* list_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_next (int /*<<< orphan*/  const*) ; 
 scalar_t__ list_node (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  osi_free (TYPE_7__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 

UINT16 L2CA_FlushChannel (UINT16 lcid, UINT16 num_to_flush)
{
    tL2C_CCB        *p_ccb;
    tL2C_LCB        *p_lcb;
    UINT16          num_left = 0,
                    num_flushed1 = 0,
                    num_flushed2 = 0;

    p_ccb = l2cu_find_ccb_by_cid(NULL, lcid);

    if ( !p_ccb || ((p_lcb = p_ccb->p_lcb) == NULL) ) {
        L2CAP_TRACE_WARNING ("L2CA_FlushChannel()  abnormally returning 0  CID: 0x%04x", lcid);
        return (0);
    }

    if (num_to_flush != L2CAP_FLUSH_CHANS_GET) {
        L2CAP_TRACE_API ("L2CA_FlushChannel (FLUSH)  CID: 0x%04x  NumToFlush: %d  QC: %u  pFirst: %p",
                         lcid, num_to_flush,
                         fixed_queue_length(p_ccb->xmit_hold_q),
                         fixed_queue_try_peek_first(p_ccb->xmit_hold_q));
    } else {
        L2CAP_TRACE_API ("L2CA_FlushChannel (QUERY)  CID: 0x%04x", lcid);
    }

    /* Cannot flush eRTM buffers once they have a sequence number */
    if (p_ccb->peer_cfg.fcr.mode != L2CAP_FCR_ERTM_MODE) {
#if L2CAP_NON_FLUSHABLE_PB_INCLUDED == TRUE
        if (num_to_flush != L2CAP_FLUSH_CHANS_GET) {
            /* If the controller supports enhanced flush, flush the data queued at the controller */
            if ( (HCI_NON_FLUSHABLE_PB_SUPPORTED(BTM_ReadLocalFeatures ()))
                    && (BTM_GetNumScoLinks() == 0) ) {
                if ( l2cb.is_flush_active == FALSE ) {
                    l2cb.is_flush_active = TRUE;

                    /* The only packet type defined - 0 - Automatically-Flushable Only */
                    btsnd_hcic_enhanced_flush (p_lcb->handle, 0);
                }
            }
        }
#endif

        // Iterate though list and flush the amount requested from
        // the transmit data queue that satisfy the layer and event conditions.
        for (const list_node_t *node = list_begin(p_lcb->link_xmit_data_q);
                (num_to_flush > 0) && node != list_end(p_lcb->link_xmit_data_q);) {
            BT_HDR *p_buf = (BT_HDR *)list_node(node);
            node = list_next(node);
            if ((p_buf->layer_specific == 0) && (p_buf->event == lcid)) {
                num_to_flush--;
                num_flushed1++;

                list_remove(p_lcb->link_xmit_data_q, p_buf);
                osi_free(p_buf);
            }
        }
    }

    /* If needed, flush buffers in the CCB xmit hold queue */
    while ( (num_to_flush != 0) && (!fixed_queue_is_empty(p_ccb->xmit_hold_q))) {
        BT_HDR *p_buf = (BT_HDR *)fixed_queue_dequeue(p_ccb->xmit_hold_q, 0);
        if (p_buf) {
            osi_free (p_buf);
        }
        num_to_flush--;
        num_flushed2++;
    }

    /* If app needs to track all packets, call him */
    if ( (p_ccb->p_rcb) && (p_ccb->p_rcb->api.pL2CA_TxComplete_Cb) && (num_flushed2) ) {
        (*p_ccb->p_rcb->api.pL2CA_TxComplete_Cb)(p_ccb->local_cid, num_flushed2);
    }

    /* Now count how many are left */
    for (const list_node_t *node = list_begin(p_lcb->link_xmit_data_q);
            node != list_end(p_lcb->link_xmit_data_q);
            node = list_next(node)) {

        BT_HDR *p_buf = (BT_HDR *)list_node(node);
        if (p_buf->event == lcid) {
            num_left++;
        }
    }

    /* Add in the number in the CCB xmit queue */
    num_left += fixed_queue_length(p_ccb->xmit_hold_q);

    /* Return the local number of buffers left for the CID */
    L2CAP_TRACE_DEBUG ("L2CA_FlushChannel()  flushed: %u + %u,  num_left: %u", num_flushed1, num_flushed2, num_left);

    /* If we were congested, and now we are not, tell the app */
    l2cu_check_channel_congestion (p_ccb);

    return (num_left);
}