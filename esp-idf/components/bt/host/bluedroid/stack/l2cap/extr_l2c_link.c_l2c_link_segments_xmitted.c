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
struct TYPE_8__ {scalar_t__ link_state; int /*<<< orphan*/  partial_segment_being_sent; int /*<<< orphan*/  link_xmit_data_q; } ;
typedef  TYPE_1__ tL2C_LCB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_9__ {int offset; } ;
typedef  TYPE_2__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HCID_GET_HANDLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ LST_CONNECTED ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2c_link_check_send_pkts (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* l2cu_find_lcb_by_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_prepend (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  osi_free (TYPE_2__*) ; 

void l2c_link_segments_xmitted (BT_HDR *p_msg)
{
    UINT8       *p = (UINT8 *)(p_msg + 1) + p_msg->offset;
    UINT16      handle;
    tL2C_LCB    *p_lcb;

    /* Extract the handle */
    STREAM_TO_UINT16 (handle, p);
    handle   = HCID_GET_HANDLE (handle);

    /* Find the LCB based on the handle */
    if ((p_lcb = l2cu_find_lcb_by_handle (handle)) == NULL) {
        L2CAP_TRACE_WARNING ("L2CAP - rcvd segment complete, unknown handle: %d\n", handle);
        osi_free (p_msg);
        return;
    }

    if (p_lcb->link_state == LST_CONNECTED) {
        /* Enqueue the buffer to the head of the transmit queue, and see */
        /* if we can transmit anything more.                             */
        list_prepend(p_lcb->link_xmit_data_q, p_msg);

        p_lcb->partial_segment_being_sent = FALSE;

        l2c_link_check_send_pkts (p_lcb, NULL, NULL);
    } else {
        osi_free (p_msg);
    }
}