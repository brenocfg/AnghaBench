#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  hooks; } ;
typedef  TYPE_1__ chassis_shutdown_hooks_t ;
struct TYPE_7__ {scalar_t__ is_called; int /*<<< orphan*/  udata; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ chassis_shutdown_hook_t ;
typedef  int /*<<< orphan*/  GString ;
typedef  int /*<<< orphan*/  GHashTableIter ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  chassis_shutdown_hooks_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  chassis_shutdown_hooks_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  g_hash_table_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_hash_table_iter_next (int /*<<< orphan*/ *,void**,void**) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void chassis_shutdown_hooks_call(chassis_shutdown_hooks_t *hooks) {
	GHashTableIter iter;
	GString *key;
	chassis_shutdown_hook_t *hook;

	chassis_shutdown_hooks_lock(hooks);
	g_hash_table_iter_init(&iter, hooks->hooks);
	while (g_hash_table_iter_next(&iter, (void **)&key, (void **)&hook)) {
		if (hook->func && !hook->is_called) hook->func(hook->udata);
		hook->is_called = TRUE;
	}
	chassis_shutdown_hooks_unlock(hooks);
}