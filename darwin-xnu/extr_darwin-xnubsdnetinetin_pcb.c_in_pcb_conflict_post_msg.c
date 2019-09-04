#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int16_t ;
struct kev_msg {TYPE_1__* dv; int /*<<< orphan*/  event_code; int /*<<< orphan*/  kev_subclass; int /*<<< orphan*/  kev_class; int /*<<< orphan*/  vendor_code; int /*<<< orphan*/  req_pid; int /*<<< orphan*/  port; } ;
struct kev_in_portinuse {TYPE_1__* dv; int /*<<< orphan*/  event_code; int /*<<< orphan*/  kev_subclass; int /*<<< orphan*/  kev_class; int /*<<< orphan*/  vendor_code; int /*<<< orphan*/  req_pid; int /*<<< orphan*/  port; } ;
struct TYPE_2__ {int data_length; struct kev_msg* data_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEV_INET_PORTINUSE ; 
 int /*<<< orphan*/  KEV_INET_SUBCLASS ; 
 int /*<<< orphan*/  KEV_NETWORK_CLASS ; 
 int /*<<< orphan*/  KEV_VENDOR_APPLE ; 
 int /*<<< orphan*/  bzero (struct kev_msg*,int) ; 
 int /*<<< orphan*/  dlil_post_complete_msg (int /*<<< orphan*/ *,struct kev_msg*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_selfpid () ; 

__attribute__((used)) static void
in_pcb_conflict_post_msg(u_int16_t port)
{
	/*
	 * Radar 5523020 send a kernel event notification if a
	 * non-participating socket tries to bind the port a socket
	 * who has set SOF_NOTIFYCONFLICT owns.
	 */
	struct kev_msg ev_msg;
	struct kev_in_portinuse	in_portinuse;

	bzero(&in_portinuse, sizeof (struct kev_in_portinuse));
	bzero(&ev_msg, sizeof (struct kev_msg));
	in_portinuse.port = ntohs(port);	/* port in host order */
	in_portinuse.req_pid = proc_selfpid();
	ev_msg.vendor_code = KEV_VENDOR_APPLE;
	ev_msg.kev_class = KEV_NETWORK_CLASS;
	ev_msg.kev_subclass = KEV_INET_SUBCLASS;
	ev_msg.event_code = KEV_INET_PORTINUSE;
	ev_msg.dv[0].data_ptr = &in_portinuse;
	ev_msg.dv[0].data_length = sizeof (struct kev_in_portinuse);
	ev_msg.dv[1].data_length = 0;
	dlil_post_complete_msg(NULL, &ev_msg);
}