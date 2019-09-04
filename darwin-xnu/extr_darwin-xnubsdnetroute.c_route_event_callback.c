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
struct sockaddr {int dummy; } ;
struct rtentry {int /*<<< orphan*/  rt_flags; int /*<<< orphan*/  rt_evhdlr_ctxt; } ;
struct route_event {int route_event_code; int /*<<< orphan*/  rt_addr; int /*<<< orphan*/ * evtag; struct rtentry* rt; } ;
typedef  int /*<<< orphan*/ * eventhandler_tag ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVENTHANDLER_INVOKE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int ROUTE_EVHDLR_DEREGISTER ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  route_event ; 
 int /*<<< orphan*/  rt_key (struct rtentry*) ; 
 int /*<<< orphan*/  rtfree (struct rtentry*) ; 

__attribute__((used)) static void
route_event_callback(void *arg)
{
	struct route_event *p_rt_ev = (struct route_event *)arg;
	struct rtentry *rt = p_rt_ev->rt;
	eventhandler_tag evtag = p_rt_ev->evtag;
	int route_ev_code = p_rt_ev->route_event_code;

	if (route_ev_code == ROUTE_EVHDLR_DEREGISTER) {
		VERIFY(evtag != NULL);
		EVENTHANDLER_DEREGISTER(&rt->rt_evhdlr_ctxt, route_event,
		    evtag);
		rtfree(rt);
		return;
	}

	EVENTHANDLER_INVOKE(&rt->rt_evhdlr_ctxt, route_event, rt_key(rt),
	    route_ev_code, (struct sockaddr *)&p_rt_ev->rt_addr,
	    rt->rt_flags);

	/* The code enqueuing the route event held a reference */
	rtfree(rt);
	/* XXX No reference is taken on gwrt */
}