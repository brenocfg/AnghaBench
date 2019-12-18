#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fscache_state {int dummy; } ;
struct fscache_object {scalar_t__ n_children; struct fscache_object* parent; int /*<<< orphan*/  lock; int /*<<< orphan*/  debug_id; int /*<<< orphan*/  cache_link; int /*<<< orphan*/  cookie_link; struct fscache_cache* cache; struct fscache_cookie* cookie; } ;
struct fscache_cookie {int /*<<< orphan*/  flags; int /*<<< orphan*/  lock; } ;
struct fscache_cache {TYPE_1__* ops; int /*<<< orphan*/  object_list_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* drop_object ) (struct fscache_object*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FSCACHE_COOKIE_INVALIDATING ; 
 int /*<<< orphan*/  FSCACHE_OBJECT_EV_CLEARED ; 
 int /*<<< orphan*/  OBJECT_DEAD ; 
 int /*<<< orphan*/  _debug (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  fscache_n_cop_drop_object ; 
 int /*<<< orphan*/  fscache_n_object_dead ; 
 int /*<<< orphan*/  fscache_put_object (struct fscache_object*) ; 
 int /*<<< orphan*/  fscache_raise_event (struct fscache_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscache_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_stat_d (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fscache_object*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct fscache_state const* transit_to (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct fscache_state *fscache_drop_object(struct fscache_object *object,
						       int event)
{
	struct fscache_object *parent = object->parent;
	struct fscache_cookie *cookie = object->cookie;
	struct fscache_cache *cache = object->cache;
	bool awaken = false;

	_enter("{OBJ%x,%d},%d", object->debug_id, object->n_children, event);

	ASSERT(cookie != NULL);
	ASSERT(!hlist_unhashed(&object->cookie_link));

	/* Make sure the cookie no longer points here and that the netfs isn't
	 * waiting for us.
	 */
	spin_lock(&cookie->lock);
	hlist_del_init(&object->cookie_link);
	if (test_and_clear_bit(FSCACHE_COOKIE_INVALIDATING, &cookie->flags))
		awaken = true;
	spin_unlock(&cookie->lock);

	if (awaken)
		wake_up_bit(&cookie->flags, FSCACHE_COOKIE_INVALIDATING);

	/* Prevent a race with our last child, which has to signal EV_CLEARED
	 * before dropping our spinlock.
	 */
	spin_lock(&object->lock);
	spin_unlock(&object->lock);

	/* Discard from the cache's collection of objects */
	spin_lock(&cache->object_list_lock);
	list_del_init(&object->cache_link);
	spin_unlock(&cache->object_list_lock);

	fscache_stat(&fscache_n_cop_drop_object);
	cache->ops->drop_object(object);
	fscache_stat_d(&fscache_n_cop_drop_object);

	/* The parent object wants to know when all it dependents have gone */
	if (parent) {
		_debug("release parent OBJ%x {%d}",
		       parent->debug_id, parent->n_children);

		spin_lock(&parent->lock);
		parent->n_children--;
		if (parent->n_children == 0)
			fscache_raise_event(parent, FSCACHE_OBJECT_EV_CLEARED);
		spin_unlock(&parent->lock);
		object->parent = NULL;
	}

	/* this just shifts the object release to the slow work processor */
	fscache_put_object(object);
	fscache_stat(&fscache_n_object_dead);

	_leave("");
	return transit_to(OBJECT_DEAD);
}