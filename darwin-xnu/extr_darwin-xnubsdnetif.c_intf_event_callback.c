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
struct intf_event {int /*<<< orphan*/  intf_event_code; int /*<<< orphan*/  addr; int /*<<< orphan*/  ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_INVOKE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_event ; 
 int /*<<< orphan*/  ifnet_evhdlr_ctxt ; 

__attribute__((used)) static void
intf_event_callback(void *arg)
{
	struct intf_event *p_intf_ev = (struct intf_event *)arg;

	/* Call this before we walk the tree */
	EVENTHANDLER_INVOKE(&ifnet_evhdlr_ctxt, ifnet_event, p_intf_ev->ifp,
	    (struct sockaddr *)&(p_intf_ev->addr), p_intf_ev->intf_event_code);
}