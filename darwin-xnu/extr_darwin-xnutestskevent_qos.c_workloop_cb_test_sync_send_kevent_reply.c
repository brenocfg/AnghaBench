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
typedef  int /*<<< orphan*/  uint64_t ;
struct kevent_qos_s {int filter; int /*<<< orphan*/  ident; } ;
typedef  int /*<<< orphan*/  mach_port_t ;

/* Variables and functions */
 int EVFILT_MACHPORT ; 
 int /*<<< orphan*/  T_ASSERT_EQ_INT (int,int,char*) ; 
 int /*<<< orphan*/  T_LOG (char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  T_SKIP (char*) ; 
 int /*<<< orphan*/  enable_kevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_reply_port (struct kevent_qos_s*) ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  send_reply (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
workloop_cb_test_sync_send_kevent_reply(uint64_t *workloop_id, struct kevent_qos_s **eventslist, int *events)
{

	T_LOG("workloop handler workloop_cb_test_sync_send_kevent_reply called");

	if (geteuid() != 0) {
		T_SKIP("kevent_qos test requires root privileges to run.");
	}

	T_QUIET; T_ASSERT_EQ_INT(*events, 1, "events received");
	T_QUIET; T_ASSERT_EQ_INT((*eventslist)->filter, EVFILT_MACHPORT, "received EVFILT_MACHPORT");

	struct kevent_qos_s *kev = *eventslist;
	mach_port_t reply_port = get_reply_port(*eventslist);

	/* Enable the knote */
	enable_kevent(workloop_id, kev->ident);

	/* send reply */
	send_reply(reply_port);

	*events = 0;

	T_LOG("Handler returning \n");
}