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
struct TYPE_4__ {int sent_not_acked; int /*<<< orphan*/  xmit_data_q; } ;
typedef  TYPE_1__ tSCO_CONN ;
struct TYPE_5__ {scalar_t__ xmit_window_size; TYPE_1__* sco_db; } ;
typedef  TYPE_2__ tSCO_CB ;
typedef  size_t UINT16 ;
struct TYPE_6__ {TYPE_2__ sco_cb; } ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,scalar_t__) ; 
 TYPE_3__ btm_cb ; 
 scalar_t__ fixed_queue_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fixed_queue_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_sco_data_to_lower (int /*<<< orphan*/ *) ; 

void btm_sco_check_send_pkts (UINT16 sco_inx)
{
    tSCO_CB  *p_cb = &btm_cb.sco_cb;
    tSCO_CONN   *p_ccb = &p_cb->sco_db[sco_inx];

    /* If there is data to send, send it now */
    BT_HDR  *p_buf;
    while (p_cb->xmit_window_size != 0)
    {
        if ((p_buf = (BT_HDR *)fixed_queue_dequeue(p_ccb->xmit_data_q, 0)) == NULL) {
            break;
        }
#if BTM_SCO_HCI_DEBUG
        BTM_TRACE_DEBUG("btm: [%d] buf in xmit_data_q",
                        fixed_queue_length(p_ccb->xmit_data_q) + 1);
#endif
        /* Don't go negative */
        p_cb->xmit_window_size -= 1;
        p_ccb->sent_not_acked += 1;

        // HCI_SCO_DATA_TO_LOWER(p_buf);
        hci_sco_data_to_lower(p_buf);
    }
}