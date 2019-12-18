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
struct dummynet_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_INVOKE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dummynet_event*) ; 
 int /*<<< orphan*/  dummynet_event ; 
 int /*<<< orphan*/  dummynet_evhdlr_ctxt ; 

__attribute__((used)) static void
dummynet_event_callback(void *arg)
{
	struct dummynet_event *p_dn_ev = (struct dummynet_event *)arg;

	EVENTHANDLER_INVOKE(&dummynet_evhdlr_ctxt, dummynet_event, p_dn_ev);
	return;
}