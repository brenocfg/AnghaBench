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
struct user_port {scalar_t__ user_ref; int /*<<< orphan*/  uport_list; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOPROTOOPT ; 
 scalar_t__ MAX_USERID ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  users ; 

int tipc_reg_remove_port(struct user_port *up_ptr)
{
	if (up_ptr->user_ref == 0)
		return 0;
	if (up_ptr->user_ref > MAX_USERID)
		return -EINVAL;
	if (!users )
		return -ENOPROTOOPT;

	spin_lock_bh(&reg_lock);
	list_del_init(&up_ptr->uport_list);
	spin_unlock_bh(&reg_lock);
	return 0;
}