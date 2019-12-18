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
struct eventhandler_lists_ctxt {int eventhandler_lists_initted; int /*<<< orphan*/  eventhandler_mutex; int /*<<< orphan*/  eventhandler_lists; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eventhandler_mutex_attr ; 
 int /*<<< orphan*/  eventhandler_mutex_grp ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
eventhandler_lists_ctxt_init(struct eventhandler_lists_ctxt *evthdlr_lists_ctxt)
{
	VERIFY(evthdlr_lists_ctxt != NULL);

	TAILQ_INIT(&evthdlr_lists_ctxt->eventhandler_lists);
	evthdlr_lists_ctxt->eventhandler_lists_initted = 1;
	lck_mtx_init(&evthdlr_lists_ctxt->eventhandler_mutex,
	    eventhandler_mutex_grp, eventhandler_mutex_attr);
}