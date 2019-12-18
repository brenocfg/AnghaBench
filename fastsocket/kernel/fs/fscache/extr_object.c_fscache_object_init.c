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
struct fscache_transition {int events; } ;
struct fscache_object {int flags; int oob_event_mask; int event_mask; TYPE_1__* state; struct fscache_transition* oob_table; int /*<<< orphan*/ * parent; struct fscache_cookie* cookie; struct fscache_cache* cache; scalar_t__ store_limit_l; scalar_t__ store_limit; scalar_t__ events; scalar_t__ n_exclusive; scalar_t__ n_in_progress; scalar_t__ n_ops; scalar_t__ n_children; int /*<<< orphan*/  pending_ops; int /*<<< orphan*/  dep_link; int /*<<< orphan*/  dependents; int /*<<< orphan*/  work; int /*<<< orphan*/  cookie_link; int /*<<< orphan*/  cache_link; int /*<<< orphan*/  lock; } ;
struct fscache_cookie {int dummy; } ;
struct fscache_cache {int /*<<< orphan*/  object_count; } ;
struct TYPE_2__ {struct fscache_transition* transitions; } ;

/* Variables and functions */
 int FSCACHE_OBJECT_IS_LIVE ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_1__* STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAIT_FOR_INIT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_object_slow_work_ops ; 
 struct fscache_transition* fscache_osm_init_oob ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vslow_work_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void fscache_object_init(struct fscache_object *object,
			 struct fscache_cookie *cookie,
			 struct fscache_cache *cache)
{
	const struct fscache_transition *t;

	atomic_inc(&cache->object_count);

	object->state = STATE(WAIT_FOR_INIT);
	object->oob_table = fscache_osm_init_oob;
	object->flags = 1 << FSCACHE_OBJECT_IS_LIVE;
	spin_lock_init(&object->lock);
	INIT_LIST_HEAD(&object->cache_link);
	INIT_HLIST_NODE(&object->cookie_link);
	vslow_work_init(&object->work, &fscache_object_slow_work_ops);
	INIT_LIST_HEAD(&object->dependents);
	INIT_LIST_HEAD(&object->dep_link);
	INIT_LIST_HEAD(&object->pending_ops);
	object->n_children = 0;
	object->n_ops = object->n_in_progress = object->n_exclusive = 0;
	object->events = 0;
	object->store_limit = 0;
	object->store_limit_l = 0;
	object->cache = cache;
	object->cookie = cookie;
	object->parent = NULL;

	object->oob_event_mask = 0;
	for (t = object->oob_table; t->events; t++)
		object->oob_event_mask |= t->events;
	object->event_mask = object->oob_event_mask;
	for (t = object->state->transitions; t->events; t++)
		object->event_mask |= t->events;
}