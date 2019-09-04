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
struct in6_event {int /*<<< orphan*/  val; int /*<<< orphan*/  in6_address; int /*<<< orphan*/  in6_ifp; int /*<<< orphan*/  in6_event_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_INVOKE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6_event ; 
 int /*<<< orphan*/  in6_evhdlr_ctxt ; 

__attribute__((used)) static void
in6_event_callback(void *arg)
{
	struct in6_event *p_in6_ev = (struct in6_event *)arg;

	EVENTHANDLER_INVOKE(&in6_evhdlr_ctxt, in6_event,
	    p_in6_ev->in6_event_code, p_in6_ev->in6_ifp,
	    &p_in6_ev->in6_address, p_in6_ev->val);
}