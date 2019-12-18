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
struct veth_lpevent {int dummy; } ;
struct HvLpEvent {int dummy; } ;

/* Variables and functions */
 scalar_t__ hvlpevent_is_ack (struct HvLpEvent*) ; 
 int /*<<< orphan*/  veth_handle_ack (struct veth_lpevent*) ; 
 int /*<<< orphan*/  veth_handle_int (struct veth_lpevent*) ; 

__attribute__((used)) static void veth_handle_event(struct HvLpEvent *event)
{
	struct veth_lpevent *veth_event = (struct veth_lpevent *)event;

	if (hvlpevent_is_ack(event))
		veth_handle_ack(veth_event);
	else
		veth_handle_int(veth_event);
}