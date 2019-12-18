#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ con_state; int /*<<< orphan*/  gap_handle; int /*<<< orphan*/  (* p_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  rx_queue_size; int /*<<< orphan*/  rx_queue; } ;
typedef  TYPE_1__ tGAP_CCB ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_8__ {scalar_t__ len; } ;
typedef  TYPE_2__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  FIXED_QUEUE_MAX_TIMEOUT ; 
 scalar_t__ GAP_CCB_STATE_CONNECTED ; 
 int /*<<< orphan*/  GAP_EVT_CONN_DATA_AVAIL ; 
 int /*<<< orphan*/  fixed_queue_enqueue (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* gap_find_ccb_by_cid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gap_data_ind (UINT16 l2cap_cid, BT_HDR *p_msg)
{
    tGAP_CCB    *p_ccb;

    /* Find CCB based on CID */
    if ((p_ccb = gap_find_ccb_by_cid (l2cap_cid)) == NULL) {
        osi_free (p_msg);
        return;
    }

    if (p_ccb->con_state == GAP_CCB_STATE_CONNECTED) {
        fixed_queue_enqueue(p_ccb->rx_queue, p_msg, FIXED_QUEUE_MAX_TIMEOUT);

        p_ccb->rx_queue_size += p_msg->len;
        /*
        GAP_TRACE_EVENT ("gap_data_ind - rx_queue_size=%d, msg len=%d",
                                       p_ccb->rx_queue_size, p_msg->len);
         */

        p_ccb->p_callback (p_ccb->gap_handle, GAP_EVT_CONN_DATA_AVAIL);
    } else {
        osi_free (p_msg);
    }
}