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
struct fscache_object {TYPE_2__* cache; int /*<<< orphan*/  debug_id; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* update_object ) (struct fscache_object*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WAIT_FOR_CMD ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  fscache_n_cop_update_object ; 
 int /*<<< orphan*/  fscache_n_updates_run ; 
 int /*<<< orphan*/  fscache_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_stat_d (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fscache_object*) ; 
 struct fscache_state const* transit_to (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct fscache_state *fscache_update_object(struct fscache_object *object,
							 int event)
{
	_enter("{OBJ%x},%d", object->debug_id, event);

	fscache_stat(&fscache_n_updates_run);
	fscache_stat(&fscache_n_cop_update_object);
	object->cache->ops->update_object(object);
	fscache_stat_d(&fscache_n_cop_update_object);

	_leave("");
	return transit_to(WAIT_FOR_CMD);
}