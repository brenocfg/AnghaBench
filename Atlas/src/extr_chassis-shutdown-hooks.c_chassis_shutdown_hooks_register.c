#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gsize ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_5__ {int /*<<< orphan*/  hooks; } ;
typedef  TYPE_1__ chassis_shutdown_hooks_t ;
typedef  int /*<<< orphan*/  chassis_shutdown_hook_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  chassis_shutdown_hooks_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  chassis_shutdown_hooks_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_hash_table_lookup_const (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_string_new_len (char const*,int /*<<< orphan*/ ) ; 

gboolean chassis_shutdown_hooks_register(chassis_shutdown_hooks_t *hooks,
		const char *key, gsize key_len,
		chassis_shutdown_hook_t *hook) {
	gboolean is_inserted = FALSE;

	chassis_shutdown_hooks_lock(hooks);
	if (NULL == g_hash_table_lookup_const(hooks->hooks, key, key_len)) {
		g_hash_table_insert(hooks->hooks, g_string_new_len(key, key_len), hook);
		is_inserted = TRUE;
	}
	chassis_shutdown_hooks_unlock(hooks);

	return is_inserted;
}