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
struct eventhandler_lists_ctxt {int /*<<< orphan*/  eventhandler_mutex; int /*<<< orphan*/  eventhandler_lists_initted; } ;
struct eventhandler_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHL_LOCK_SPIN (struct eventhandler_list*) ; 
 struct eventhandler_list* _eventhandler_find_list (struct eventhandler_lists_ctxt*,char const*) ; 
 struct eventhandler_lists_ctxt evthdlr_lists_ctxt_glb ; 
 int /*<<< orphan*/  lck_mtx_convert_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

struct eventhandler_list *
eventhandler_find_list(struct eventhandler_lists_ctxt *evthdlr_lists_ctxt,
    const char *name)
{
	struct eventhandler_list	*list;

	if (evthdlr_lists_ctxt == NULL)
		evthdlr_lists_ctxt = &evthdlr_lists_ctxt_glb;

	if (!evthdlr_lists_ctxt->eventhandler_lists_initted)
		return(NULL);

	/* scan looking for the requested list */
	lck_mtx_lock_spin(&evthdlr_lists_ctxt->eventhandler_mutex);
	list = _eventhandler_find_list(evthdlr_lists_ctxt, name);
	if (list != NULL) {
		lck_mtx_convert_spin(&evthdlr_lists_ctxt->eventhandler_mutex);
		EHL_LOCK_SPIN(list);
	}
	lck_mtx_unlock(&evthdlr_lists_ctxt->eventhandler_mutex);

	return(list);
}