#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ con_state; scalar_t__ is_congested; int /*<<< orphan*/  connection_id; int /*<<< orphan*/  tx_queue; } ;
typedef  TYPE_1__ tGAP_CCB ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_9__ {scalar_t__ offset; } ;
typedef  TYPE_2__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  BT_PASS ; 
 int /*<<< orphan*/  FIXED_QUEUE_MAX_TIMEOUT ; 
 scalar_t__ GAP_CCB_STATE_CONNECTED ; 
 int /*<<< orphan*/  GAP_ERR_BAD_HANDLE ; 
 int /*<<< orphan*/  GAP_ERR_BAD_STATE ; 
 int /*<<< orphan*/  GAP_ERR_BUF_OFFSET ; 
 scalar_t__ L2CAP_DW_CONGESTED ; 
 scalar_t__ L2CAP_DW_SUCCESS ; 
 scalar_t__ L2CAP_MIN_OFFSET ; 
 scalar_t__ L2CA_DATA_WRITE (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ TRUE ; 
 scalar_t__ fixed_queue_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixed_queue_enqueue (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* gap_find_ccb_by_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gap_send_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free (TYPE_2__*) ; 

UINT16 GAP_ConnBTWrite (UINT16 gap_handle, BT_HDR *p_buf)
{
    tGAP_CCB    *p_ccb = gap_find_ccb_by_handle (gap_handle);

    if (!p_ccb) {
        osi_free (p_buf);
        return (GAP_ERR_BAD_HANDLE);
    }

    if (p_ccb->con_state != GAP_CCB_STATE_CONNECTED) {
        osi_free (p_buf);
        return (GAP_ERR_BAD_STATE);
    }

    if (p_buf->offset < L2CAP_MIN_OFFSET) {
        osi_free (p_buf);
        return (GAP_ERR_BUF_OFFSET);
    }

    fixed_queue_enqueue(p_ccb->tx_queue, p_buf, FIXED_QUEUE_MAX_TIMEOUT);

    if (p_ccb->is_congested) {
        return (BT_PASS);
    }

    /* Send the buffer through L2CAP */
#if (GAP_CONN_POST_EVT_INCLUDED == TRUE)
    gap_send_event (gap_handle);
#else
    while ((p_buf = (BT_HDR *)fixed_queue_dequeue(p_ccb->tx_queue, 0)) != NULL) {
        UINT8 status = L2CA_DATA_WRITE (p_ccb->connection_id, p_buf);

        if (status == L2CAP_DW_CONGESTED) {
            p_ccb->is_congested = TRUE;
            break;
        } else if (status != L2CAP_DW_SUCCESS) {
            return (GAP_ERR_BAD_STATE);
        }
    }
#endif
    return (BT_PASS);
}