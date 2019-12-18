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
struct debug_obj_descr {int /*<<< orphan*/  fixup_init; } ;
struct debug_obj {int state; } ;
struct debug_bucket {int /*<<< orphan*/  lock; } ;
typedef  enum debug_obj_state { ____Placeholder_debug_obj_state } debug_obj_state ;

/* Variables and functions */
#define  ODEBUG_STATE_ACTIVE 132 
#define  ODEBUG_STATE_DESTROYED 131 
#define  ODEBUG_STATE_INACTIVE 130 
#define  ODEBUG_STATE_INIT 129 
#define  ODEBUG_STATE_NONE 128 
 struct debug_obj* alloc_object (void*,struct debug_bucket*,struct debug_obj_descr*) ; 
 int /*<<< orphan*/  debug_object_fixup (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  debug_object_is_on_stack (void*,int) ; 
 scalar_t__ debug_objects_enabled ; 
 int /*<<< orphan*/  debug_objects_oom () ; 
 int /*<<< orphan*/  debug_print_object (struct debug_obj*,char*) ; 
 int /*<<< orphan*/  fill_pool () ; 
 struct debug_bucket* get_bucket (unsigned long) ; 
 struct debug_obj* lookup_object (void*,struct debug_bucket*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
__debug_object_init(void *addr, struct debug_obj_descr *descr, int onstack)
{
	enum debug_obj_state state;
	struct debug_bucket *db;
	struct debug_obj *obj;
	unsigned long flags;

	fill_pool();

	db = get_bucket((unsigned long) addr);

	spin_lock_irqsave(&db->lock, flags);

	obj = lookup_object(addr, db);
	if (!obj) {
		obj = alloc_object(addr, db, descr);
		if (!obj) {
			debug_objects_enabled = 0;
			spin_unlock_irqrestore(&db->lock, flags);
			debug_objects_oom();
			return;
		}
		debug_object_is_on_stack(addr, onstack);
	}

	switch (obj->state) {
	case ODEBUG_STATE_NONE:
	case ODEBUG_STATE_INIT:
	case ODEBUG_STATE_INACTIVE:
		obj->state = ODEBUG_STATE_INIT;
		break;

	case ODEBUG_STATE_ACTIVE:
		debug_print_object(obj, "init");
		state = obj->state;
		spin_unlock_irqrestore(&db->lock, flags);
		debug_object_fixup(descr->fixup_init, addr, state);
		return;

	case ODEBUG_STATE_DESTROYED:
		debug_print_object(obj, "init");
		break;
	default:
		break;
	}

	spin_unlock_irqrestore(&db->lock, flags);
}