#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ con_state; int /*<<< orphan*/  rx_queue_size; } ;
typedef  TYPE_2__ tGAP_CCB ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  size_t UINT16 ;
struct TYPE_4__ {TYPE_2__* ccb_pool; } ;
struct TYPE_6__ {TYPE_1__ conn; } ;

/* Variables and functions */
 int BT_PASS ; 
 scalar_t__ GAP_CCB_STATE_CONNECTED ; 
 int GAP_INVALID_HANDLE ; 
 size_t GAP_MAX_CONNECTIONS ; 
 int /*<<< orphan*/  GAP_TRACE_EVENT (char*,int,int /*<<< orphan*/ ) ; 
 TYPE_3__ gap_cb ; 

int GAP_GetRxQueueCnt (UINT16 handle, UINT32 *p_rx_queue_count)
{
    tGAP_CCB    *p_ccb;
    int         rc = BT_PASS;

    /* Check that handle is valid */
    if (handle < GAP_MAX_CONNECTIONS) {
        p_ccb = &gap_cb.conn.ccb_pool[handle];

        if (p_ccb->con_state == GAP_CCB_STATE_CONNECTED) {
            *p_rx_queue_count = p_ccb->rx_queue_size;
        } else {
            rc = GAP_INVALID_HANDLE;
        }
    } else {
        rc = GAP_INVALID_HANDLE;
    }

    GAP_TRACE_EVENT ("GAP_GetRxQueueCnt - rc = 0x%04x, rx_queue_count=%d",
                     rc , *p_rx_queue_count);

    return (rc);
}