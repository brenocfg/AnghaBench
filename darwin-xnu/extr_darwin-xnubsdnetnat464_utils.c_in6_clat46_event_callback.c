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
struct kev_netevent_clat46_data {int /*<<< orphan*/  euuid; int /*<<< orphan*/  epid; int /*<<< orphan*/  clat46_event_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_INVOKE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6_clat46_event ; 
 int /*<<< orphan*/  in6_clat46_evhdlr_ctxt ; 

__attribute__((used)) static void
in6_clat46_event_callback(void *arg)
{
        struct kev_netevent_clat46_data *p_in6_clat46_ev =
            (struct kev_netevent_clat46_data *)arg;

        EVENTHANDLER_INVOKE(&in6_clat46_evhdlr_ctxt, in6_clat46_event,
            p_in6_clat46_ev->clat46_event_code, p_in6_clat46_ev->epid,
            p_in6_clat46_ev->euuid);
}