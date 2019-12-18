#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fscache_state {int dummy; } ;
struct fscache_object {struct fscache_cookie* cookie; TYPE_2__* cache; scalar_t__ oob_event_mask; int /*<<< orphan*/  debug_id; } ;
struct fscache_cookie {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* lookup_complete ) (struct fscache_object*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FSCACHE_COOKIE_LOOKING_UP ; 
 int /*<<< orphan*/  FSCACHE_COOKIE_UNAVAILABLE ; 
 int /*<<< orphan*/  KILL_OBJECT ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fscache_done_parent_op (struct fscache_object*) ; 
 int /*<<< orphan*/  fscache_n_cop_lookup_complete ; 
 int /*<<< orphan*/  fscache_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_stat_d (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fscache_object*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct fscache_state const* transit_to (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct fscache_state *fscache_lookup_failure(struct fscache_object *object,
							  int event)
{
	struct fscache_cookie *cookie;

	_enter("{OBJ%x},%d", object->debug_id, event);

	object->oob_event_mask = 0;

	fscache_stat(&fscache_n_cop_lookup_complete);
	object->cache->ops->lookup_complete(object);
	fscache_stat_d(&fscache_n_cop_lookup_complete);

	cookie = object->cookie;
	set_bit(FSCACHE_COOKIE_UNAVAILABLE, &cookie->flags);
	if (test_and_clear_bit(FSCACHE_COOKIE_LOOKING_UP, &cookie->flags))
		wake_up_bit(&cookie->flags, FSCACHE_COOKIE_LOOKING_UP);

	fscache_done_parent_op(object);
	return transit_to(KILL_OBJECT);
}