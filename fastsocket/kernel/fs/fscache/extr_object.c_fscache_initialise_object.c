#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fscache_state {int dummy; } ;
struct fscache_object {int /*<<< orphan*/  lock; int /*<<< orphan*/  dependents; int /*<<< orphan*/  dep_link; TYPE_3__* cache; int /*<<< orphan*/  flags; TYPE_1__* state; struct fscache_object* parent; int /*<<< orphan*/  debug_id; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {scalar_t__ (* grab_object ) (struct fscache_object*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DROP_OBJECT ; 
 int /*<<< orphan*/  FSCACHE_OBJECT_EV_NEW_CHILD ; 
 int /*<<< orphan*/  PARENT_READY ; 
 int /*<<< orphan*/  WAIT_FOR_PARENT ; 
 int /*<<< orphan*/  _debug (char*,...) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  fscache_n_cop_grab_object ; 
 scalar_t__ fscache_object_is_available (struct fscache_object*) ; 
 scalar_t__ fscache_object_is_dying (struct fscache_object*) ; 
 scalar_t__ fscache_object_is_live (struct fscache_object*) ; 
 int /*<<< orphan*/  fscache_raise_event (struct fscache_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscache_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_stat_d (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct fscache_object*) ; 
 struct fscache_state const* transit_to (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct fscache_state *fscache_initialise_object(struct fscache_object *object,
							     int event)
{
	struct fscache_object *parent;
	bool success;

	_enter("{OBJ%x},%d", object->debug_id, event);

	ASSERT(list_empty(&object->dep_link));

	parent = object->parent;
	if (!parent) {
		_leave(" [no parent]");
		return transit_to(DROP_OBJECT);
	}

	_debug("parent: %s of:%lx", parent->state->name, parent->flags);

	if (fscache_object_is_dying(parent)) {
		_leave(" [bad parent]");
		return transit_to(DROP_OBJECT);
	}

	if (fscache_object_is_available(parent)) {
		_leave(" [ready]");
		return transit_to(PARENT_READY);
	}

	_debug("wait");

	spin_lock(&parent->lock);
	fscache_stat(&fscache_n_cop_grab_object);
	success = false;
	if (fscache_object_is_live(parent) &&
	    object->cache->ops->grab_object(object)) {
		list_add(&object->dep_link, &parent->dependents);
		success = true;
	}
	fscache_stat_d(&fscache_n_cop_grab_object);
	spin_unlock(&parent->lock);
	if (!success) {
		_leave(" [grab failed]");
		return transit_to(DROP_OBJECT);
	}

	/* fscache_acquire_non_index_cookie() uses this
	 * to wake the chain up */
	fscache_raise_event(parent, FSCACHE_OBJECT_EV_NEW_CHILD);
	_leave(" [wait]");
	return transit_to(WAIT_FOR_PARENT);
}