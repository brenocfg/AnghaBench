#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* bondport_ref ;
struct TYPE_9__ {int po_receive_state; } ;
typedef  int /*<<< orphan*/  LAEvent ;

/* Variables and functions */
 int /*<<< orphan*/  LAEventStart ; 
#define  ReceiveState_CURRENT 134 
#define  ReceiveState_DEFAULTED 133 
#define  ReceiveState_EXPIRED 132 
#define  ReceiveState_INITIALIZE 131 
#define  ReceiveState_LACP_DISABLED 130 
#define  ReceiveState_PORT_DISABLED 129 
#define  ReceiveState_none 128 
 int /*<<< orphan*/  bondport_receive_machine_current (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  bondport_receive_machine_defaulted (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  bondport_receive_machine_expired (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  bondport_receive_machine_initialize (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  bondport_receive_machine_lacp_disabled (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  bondport_receive_machine_port_disabled (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
bondport_receive_machine_event(bondport_ref p, LAEvent event, 
			       void * event_data)
{
    switch (p->po_receive_state) {
    case ReceiveState_none:
	bondport_receive_machine_initialize(p, LAEventStart, NULL);
	break;
    case ReceiveState_INITIALIZE:
	bondport_receive_machine_initialize(p, event, event_data);
	break;
    case ReceiveState_PORT_DISABLED:
	bondport_receive_machine_port_disabled(p, event, event_data);
	break;
    case ReceiveState_EXPIRED:
	bondport_receive_machine_expired(p, event, event_data);
	break;
    case ReceiveState_LACP_DISABLED:
	bondport_receive_machine_lacp_disabled(p, event, event_data);
	break;
    case ReceiveState_DEFAULTED:
	bondport_receive_machine_defaulted(p, event, event_data);
	break;
    case ReceiveState_CURRENT:
	bondport_receive_machine_current(p, event, event_data);
	break;
    default:
	break;
    }
    return;
}