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
struct ip_mc_list {struct ip_mc_list* next; } ;
struct in_device {int /*<<< orphan*/  mc_list_lock; int /*<<< orphan*/  mc_count; struct ip_mc_list* mc_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  ip_ma_put (struct ip_mc_list*) ; 
 int /*<<< orphan*/  ip_mc_clear_src (struct ip_mc_list*) ; 
 int /*<<< orphan*/  ip_mc_down (struct in_device*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void ip_mc_destroy_dev(struct in_device *in_dev)
{
	struct ip_mc_list *i;

	ASSERT_RTNL();

	/* Deactivate timers */
	ip_mc_down(in_dev);

	write_lock_bh(&in_dev->mc_list_lock);
	while ((i = in_dev->mc_list) != NULL) {
		in_dev->mc_list = i->next;
		in_dev->mc_count--;
		write_unlock_bh(&in_dev->mc_list_lock);

		/* We've dropped the groups in ip_mc_down already */
		ip_mc_clear_src(i);
		ip_ma_put(i);

		write_lock_bh(&in_dev->mc_list_lock);
	}
	write_unlock_bh(&in_dev->mc_list_lock);
}