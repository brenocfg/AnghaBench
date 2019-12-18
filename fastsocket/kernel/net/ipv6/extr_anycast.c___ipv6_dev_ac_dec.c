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
struct inet6_dev {int /*<<< orphan*/  lock; struct ifacaddr6* ac_list; } ;
struct in6_addr {int dummy; } ;
struct ifacaddr6 {scalar_t__ aca_users; TYPE_2__* aca_rt; int /*<<< orphan*/  aca_addr; struct ifacaddr6* aca_next; } ;
struct TYPE_3__ {int /*<<< orphan*/  dst; } ;
struct TYPE_4__ {TYPE_1__ u; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  aca_put (struct ifacaddr6*) ; 
 int /*<<< orphan*/  addrconf_leave_solict (struct inet6_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip6_del_rt (TYPE_2__*) ; 
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,struct in6_addr*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int __ipv6_dev_ac_dec(struct inet6_dev *idev, struct in6_addr *addr)
{
	struct ifacaddr6 *aca, *prev_aca;

	write_lock_bh(&idev->lock);
	prev_aca = NULL;
	for (aca = idev->ac_list; aca; aca = aca->aca_next) {
		if (ipv6_addr_equal(&aca->aca_addr, addr))
			break;
		prev_aca = aca;
	}
	if (!aca) {
		write_unlock_bh(&idev->lock);
		return -ENOENT;
	}
	if (--aca->aca_users > 0) {
		write_unlock_bh(&idev->lock);
		return 0;
	}
	if (prev_aca)
		prev_aca->aca_next = aca->aca_next;
	else
		idev->ac_list = aca->aca_next;
	write_unlock_bh(&idev->lock);
	addrconf_leave_solict(idev, &aca->aca_addr);

	dst_hold(&aca->aca_rt->u.dst);
	ip6_del_rt(aca->aca_rt);

	aca_put(aca);
	return 0;
}