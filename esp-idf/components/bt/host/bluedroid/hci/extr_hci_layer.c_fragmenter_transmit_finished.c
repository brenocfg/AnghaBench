#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  dispatch_reassembled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fragmenter_transmit_finished(BT_HDR *packet, bool all_fragments_sent)
{
    if (all_fragments_sent) {
        osi_free(packet);
    } else {
        // This is kind of a weird case, since we're dispatching a partially sent packet
        // up to a higher layer.
        // TODO(zachoverflow): rework upper layer so this isn't necessary.
        //osi_free(packet);

        /* dispatch_reassembled(packet) will send the packet back to the higher layer
           when controller buffer is not enough. hci will send the remain packet back
           to the l2cap layer and saved in the Link Queue (p_lcb->link_xmit_data_q).
           The l2cap layer will resend the packet to lower layer when controller buffer
           can be used.
        */

        dispatch_reassembled(packet);
        //data_dispatcher_dispatch(interface.event_dispatcher, packet->event & MSG_EVT_MASK, packet);
    }
}