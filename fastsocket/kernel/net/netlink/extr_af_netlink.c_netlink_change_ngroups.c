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
struct sock {int dummy; } ;

/* Variables and functions */
 int __netlink_change_ngroups (struct sock*,unsigned int) ; 
 int /*<<< orphan*/  netlink_table_grab () ; 
 int /*<<< orphan*/  netlink_table_ungrab () ; 

int netlink_change_ngroups(struct sock *sk, unsigned int groups)
{
	int err;

	netlink_table_grab();
	err = __netlink_change_ngroups(sk, groups);
	netlink_table_ungrab();

	return err;
}