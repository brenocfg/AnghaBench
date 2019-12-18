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
typedef  int /*<<< orphan*/  (* tipc_mode_event ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
struct tipc_user {void* usr_handle; int /*<<< orphan*/  (* callback ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  reg_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_mode ; 
 int /*<<< orphan*/  tipc_own_addr ; 

__attribute__((used)) static void reg_callback(struct tipc_user *user_ptr)
{
	tipc_mode_event cb;
	void *arg;

	spin_lock_bh(&reg_lock);
	cb = user_ptr->callback;
	arg = user_ptr->usr_handle;
	spin_unlock_bh(&reg_lock);

	if (cb)
		cb(arg, tipc_mode, tipc_own_addr);
}