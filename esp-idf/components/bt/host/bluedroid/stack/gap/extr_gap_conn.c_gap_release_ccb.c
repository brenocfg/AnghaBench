#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ psm; scalar_t__ con_state; int /*<<< orphan*/ * tx_queue; int /*<<< orphan*/ * rx_queue; scalar_t__ rx_queue_size; int /*<<< orphan*/  service_id; } ;
typedef  TYPE_2__ tGAP_CCB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_5__ {TYPE_2__* ccb_pool; } ;
struct TYPE_7__ {TYPE_1__ conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_SecClrService (int /*<<< orphan*/ ) ; 
 scalar_t__ GAP_CCB_STATE_IDLE ; 
 scalar_t__ GAP_MAX_CONNECTIONS ; 
 int /*<<< orphan*/  L2CA_DEREGISTER (scalar_t__) ; 
 int /*<<< orphan*/  fixed_queue_dequeue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixed_queue_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fixed_queue_is_empty (int /*<<< orphan*/ *) ; 
 TYPE_4__ gap_cb ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gap_release_ccb (tGAP_CCB *p_ccb)
{
    UINT16       xx;
    UINT16      psm = p_ccb->psm;
    UINT8       service_id = p_ccb->service_id;

    /* Drop any buffers we may be holding */
    p_ccb->rx_queue_size = 0;

    while (!fixed_queue_is_empty(p_ccb->rx_queue)) {
        osi_free(fixed_queue_dequeue(p_ccb->rx_queue, 0));
	}
    fixed_queue_free(p_ccb->rx_queue, NULL);
    p_ccb->rx_queue = NULL;

    while (!fixed_queue_is_empty(p_ccb->tx_queue)) {
        osi_free(fixed_queue_dequeue(p_ccb->tx_queue, 0));
	}
    fixed_queue_free(p_ccb->tx_queue, NULL);
    p_ccb->tx_queue = NULL;

    p_ccb->con_state = GAP_CCB_STATE_IDLE;

    /* If no-one else is using the PSM, deregister from L2CAP */
    for (xx = 0, p_ccb = gap_cb.conn.ccb_pool; xx < GAP_MAX_CONNECTIONS; xx++, p_ccb++) {
        if ((p_ccb->con_state != GAP_CCB_STATE_IDLE) && (p_ccb->psm == psm)) {
            return;
        }
    }
#if (SDP_INCLUDED == TRUE)
    /* Free the security record for this PSM */
    BTM_SecClrService(service_id);
#endif  ///SDP_INCLUDED == TRUE
    L2CA_DEREGISTER (psm);
}