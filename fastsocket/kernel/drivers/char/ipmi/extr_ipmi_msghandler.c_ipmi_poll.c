#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ipmi_smi_t ;
struct TYPE_6__ {int /*<<< orphan*/  send_info; TYPE_1__* handlers; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* poll ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  handle_new_recv_msgs (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipmi_poll(ipmi_smi_t intf)
{
	if (intf->handlers->poll)
		intf->handlers->poll(intf->send_info);
	/* In case something came in */
	handle_new_recv_msgs(intf);
}