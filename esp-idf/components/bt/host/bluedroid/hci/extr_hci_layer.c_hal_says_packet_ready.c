#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* reassemble_and_dispatch ) (TYPE_1__*) ;} ;
struct TYPE_7__ {scalar_t__ event; } ;
typedef  TYPE_1__ BT_HDR ;

/* Variables and functions */
 scalar_t__ MSG_HC_TO_STACK_HCI_EVT ; 
 int /*<<< orphan*/  dispatch_reassembled (TYPE_1__*) ; 
 int /*<<< orphan*/  filter_incoming_event (TYPE_1__*) ; 
 TYPE_3__* packet_fragmenter ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void hal_says_packet_ready(BT_HDR *packet)
{
    if (packet->event != MSG_HC_TO_STACK_HCI_EVT) {
        packet_fragmenter->reassemble_and_dispatch(packet);
    } else if (!filter_incoming_event(packet)) {
        dispatch_reassembled(packet);
    }
}