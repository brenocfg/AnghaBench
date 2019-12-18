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
struct fscache_operation {int /*<<< orphan*/  debug_id; struct fscache_object* object; } ;
struct fscache_object {TYPE_2__* cache; int /*<<< orphan*/  debug_id; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* attr_changed ) (struct fscache_object*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  fscache_abort_object (struct fscache_object*) ; 
 int /*<<< orphan*/  fscache_n_attr_changed_calls ; 
 int /*<<< orphan*/  fscache_n_cop_attr_changed ; 
 scalar_t__ fscache_object_is_active (struct fscache_object*) ; 
 int /*<<< orphan*/  fscache_op_complete (struct fscache_operation*,int) ; 
 int /*<<< orphan*/  fscache_set_op_state (struct fscache_operation*,char*) ; 
 int /*<<< orphan*/  fscache_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_stat_d (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_unuse_cookie (struct fscache_object*) ; 
 scalar_t__ fscache_use_cookie (struct fscache_object*) ; 
 int stub1 (struct fscache_object*) ; 

__attribute__((used)) static void fscache_attr_changed_op(struct fscache_operation *op)
{
	struct fscache_object *object = op->object;
	int ret;

	_enter("{OBJ%x OP%x}", object->debug_id, op->debug_id);

	fscache_stat(&fscache_n_attr_changed_calls);

	if (fscache_object_is_active(object) &&
	    fscache_use_cookie(object)) {
		fscache_set_op_state(op, "CallFS");
		fscache_stat(&fscache_n_cop_attr_changed);
		ret = object->cache->ops->attr_changed(object);
		fscache_stat_d(&fscache_n_cop_attr_changed);
		fscache_set_op_state(op, "Done");
		fscache_unuse_cookie(object);
		if (ret < 0)
			fscache_abort_object(object);
	}

	fscache_op_complete(op, true);
	_leave("");
}