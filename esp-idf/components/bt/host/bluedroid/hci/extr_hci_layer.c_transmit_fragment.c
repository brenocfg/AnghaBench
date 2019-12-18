#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  serial_data_type_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* transmit_data ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {scalar_t__ event; int /*<<< orphan*/  len; scalar_t__ offset; scalar_t__ data; } ;
typedef  TYPE_1__ BT_HDR ;

/* Variables and functions */
 scalar_t__ MSG_EVT_MASK ; 
 scalar_t__ MSG_STACK_TO_HC_HCI_CMD ; 
 int /*<<< orphan*/  event_to_data_type (scalar_t__) ; 
 TYPE_4__* hal ; 
 int /*<<< orphan*/  osi_free (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void transmit_fragment(BT_HDR *packet, bool send_transmit_finished)
{
    uint16_t event = packet->event & MSG_EVT_MASK;
    serial_data_type_t type = event_to_data_type(event);

    hal->transmit_data(type, packet->data + packet->offset, packet->len);

    if (event != MSG_STACK_TO_HC_HCI_CMD && send_transmit_finished) {
        osi_free(packet);
    }
}