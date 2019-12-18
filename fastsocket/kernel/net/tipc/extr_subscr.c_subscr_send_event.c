#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tipc_event {int dummy; } ;
struct TYPE_3__ {void* node; void* ref; } ;
struct TYPE_4__ {TYPE_1__ port; void* found_upper; void* found_lower; void* event; } ;
struct subscription {int /*<<< orphan*/  server_ref; int /*<<< orphan*/  swap; TYPE_2__ evt; } ;
struct iovec {int iov_len; void* iov_base; } ;

/* Variables and functions */
 void* htohl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_send (int /*<<< orphan*/ ,int,struct iovec*) ; 

__attribute__((used)) static void subscr_send_event(struct subscription *sub,
			      u32 found_lower,
			      u32 found_upper,
			      u32 event,
			      u32 port_ref,
			      u32 node)
{
	struct iovec msg_sect;

	msg_sect.iov_base = (void *)&sub->evt;
	msg_sect.iov_len = sizeof(struct tipc_event);

	sub->evt.event = htohl(event, sub->swap);
	sub->evt.found_lower = htohl(found_lower, sub->swap);
	sub->evt.found_upper = htohl(found_upper, sub->swap);
	sub->evt.port.ref = htohl(port_ref, sub->swap);
	sub->evt.port.node = htohl(node, sub->swap);
	tipc_send(sub->server_ref, 1, &msg_sect);
}