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
typedef  int /*<<< orphan*/  uuid_t ;
struct TYPE_2__ {int /*<<< orphan*/  valid_uuid; int /*<<< orphan*/  volume_uuid; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ cp_lock_vfs_callback_arg ;
typedef  int cp_key_store_action_t ;

/* Variables and functions */
#define  CP_ACTION_LOCKED 129 
#define  CP_ACTION_UNLOCKED 128 
 int /*<<< orphan*/  CP_LOCKED_STATE ; 
 int /*<<< orphan*/  CP_UNLOCKED_STATE ; 
 int /*<<< orphan*/  cp_lock_vfs_callback ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vfs_iterate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int
cp_key_store_action(cp_key_store_action_t action)
{
	cp_lock_vfs_callback_arg callback_arg;

	switch (action) {
		case CP_ACTION_LOCKED:
		case CP_ACTION_UNLOCKED:
			callback_arg.state = (action == CP_ACTION_LOCKED ? CP_LOCKED_STATE : CP_UNLOCKED_STATE);
			memset(callback_arg.volume_uuid, 0, sizeof(uuid_t));
			callback_arg.valid_uuid = 0;
			return vfs_iterate(0, cp_lock_vfs_callback, (void *)&callback_arg);
		default:
			return -1;
	}
}