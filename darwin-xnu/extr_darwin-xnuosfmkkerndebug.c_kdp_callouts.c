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
struct kdp_callout {struct kdp_callout* callout_next; scalar_t__ callout_in_progress; int /*<<< orphan*/  callout_arg; int /*<<< orphan*/  (* callout_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  kdp_event_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 struct kdp_callout* kdp_callout_list ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kdp_callouts(kdp_event_t event)
{
	struct kdp_callout	*kcp = kdp_callout_list;

	while (kcp) {
		if (!kcp->callout_in_progress) {
			kcp->callout_in_progress = TRUE;
			kcp->callout_fn(kcp->callout_arg, event);
			kcp->callout_in_progress = FALSE;
		}
		kcp = kcp->callout_next;
	}
}