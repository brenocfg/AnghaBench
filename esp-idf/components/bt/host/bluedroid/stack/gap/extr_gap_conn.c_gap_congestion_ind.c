#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ is_congested; int /*<<< orphan*/  connection_id; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  gap_handle; int /*<<< orphan*/  (* p_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ tGAP_CCB ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BT_HDR ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  GAP_EVT_CONN_CONGESTED ; 
 int /*<<< orphan*/  GAP_EVT_CONN_UNCONGESTED ; 
 int /*<<< orphan*/  GAP_TRACE_EVENT (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ L2CAP_DW_CONGESTED ; 
 scalar_t__ L2CAP_DW_SUCCESS ; 
 scalar_t__ L2CA_DATA_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 scalar_t__ fixed_queue_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* gap_find_ccb_by_cid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gap_congestion_ind (UINT16 lcid, BOOLEAN is_congested)
{
    tGAP_CCB    *p_ccb;
    UINT16       event;
    BT_HDR      *p_buf;
    UINT8        status;

    GAP_TRACE_EVENT ("GAP_CONN - Rcvd L2CAP Is Congested (%d), CID: 0x%x",
                     is_congested, lcid);

    /* Find CCB based on CID */
    if ((p_ccb = gap_find_ccb_by_cid (lcid)) == NULL) {
        return;
    }

    p_ccb->is_congested = is_congested;

    event = (is_congested) ? GAP_EVT_CONN_CONGESTED : GAP_EVT_CONN_UNCONGESTED;
    p_ccb->p_callback (p_ccb->gap_handle, event);

    if (!is_congested) {
        while ((p_buf = (BT_HDR *)fixed_queue_dequeue(p_ccb->tx_queue, 0)) != NULL) {
            status = L2CA_DATA_WRITE (p_ccb->connection_id, p_buf);

            if (status == L2CAP_DW_CONGESTED) {
                p_ccb->is_congested = TRUE;
                break;
            } else if (status != L2CAP_DW_SUCCESS) {
                break;
            }
        }
    }
}