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
struct user_port {size_t user_ref; int /*<<< orphan*/  uport_list; } ;
struct tipc_user {int /*<<< orphan*/  ports; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOPROTOOPT ; 
 size_t MAX_USERID ; 
 scalar_t__ TIPC_NOT_RUNNING ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ tipc_mode ; 
 struct tipc_user* users ; 

int tipc_reg_add_port(struct user_port *up_ptr)
{
	struct tipc_user *user_ptr;

	if (up_ptr->user_ref == 0)
		return 0;
	if (up_ptr->user_ref > MAX_USERID)
		return -EINVAL;
	if ((tipc_mode == TIPC_NOT_RUNNING) || !users )
		return -ENOPROTOOPT;

	spin_lock_bh(&reg_lock);
	user_ptr = &users[up_ptr->user_ref];
	list_add(&up_ptr->uport_list, &user_ptr->ports);
	spin_unlock_bh(&reg_lock);
	return 0;
}