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
struct eventhandler_list {int dummy; } ;
struct eventhandler_entry_generic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCR_SLEEP ; 
 void* eg_cache ; 
 int eg_size ; 
 void* el_cache ; 
 void* el_lock_attr ; 
 void* el_lock_grp ; 
 int /*<<< orphan*/  el_lock_grp_attr ; 
 int el_size ; 
 int /*<<< orphan*/  eventhandler_lists_ctxt_init (int /*<<< orphan*/ *) ; 
 void* eventhandler_mutex_attr ; 
 void* eventhandler_mutex_grp ; 
 int /*<<< orphan*/  eventhandler_mutex_grp_attr ; 
 int /*<<< orphan*/  evthdlr_lists_ctxt_glb ; 
 void* lck_attr_alloc_init () ; 
 void* lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 void* mcache_create (char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
eventhandler_init(void)
{
	eventhandler_mutex_grp_attr = lck_grp_attr_alloc_init();
	eventhandler_mutex_grp = lck_grp_alloc_init("eventhandler",
	    eventhandler_mutex_grp_attr);
	eventhandler_mutex_attr = lck_attr_alloc_init();

	el_lock_grp_attr = lck_grp_attr_alloc_init();
	el_lock_grp = lck_grp_alloc_init("eventhandler list",
	    el_lock_grp_attr);
	el_lock_attr = lck_attr_alloc_init();

	eventhandler_lists_ctxt_init(&evthdlr_lists_ctxt_glb);

	eg_size = sizeof (struct eventhandler_entry_generic);
	eg_cache = mcache_create("eventhdlr_generic", eg_size,
	    sizeof (uint64_t), 0, MCR_SLEEP);

	el_size = sizeof (struct eventhandler_list);
	el_cache = mcache_create("eventhdlr_list", el_size,
	    sizeof (uint64_t), 0, MCR_SLEEP);
}