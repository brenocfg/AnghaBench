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

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eventhandler_entry_dummy_arg ; 
 int /*<<< orphan*/  eventhandler_lists_ctxt_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_low_power_event ; 
 int /*<<< orphan*/  if_low_power_evhdlr_callback ; 
 int /*<<< orphan*/  if_low_power_evhdlr_ctx ; 

void
if_low_power_evhdlr_init(void)
{
	eventhandler_lists_ctxt_init(&if_low_power_evhdlr_ctx);

	(void) EVENTHANDLER_REGISTER(&if_low_power_evhdlr_ctx,
	    if_low_power_event,
	    if_low_power_evhdlr_callback, 
	    eventhandler_entry_dummy_arg,
	    EVENTHANDLER_PRI_ANY);
}