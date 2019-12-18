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
struct sock {int dummy; } ;
struct ipv6_mc_socklist {TYPE_1__* sflist; int /*<<< orphan*/  sfmode; int /*<<< orphan*/  addr; } ;
struct inet6_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sl_max; int /*<<< orphan*/ * sl_addr; int /*<<< orphan*/  sl_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP6_SFLSIZE (int /*<<< orphan*/ ) ; 
 int ip6_mc_del_src (struct inet6_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_kfree_s (struct sock*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip6_mc_leave_src(struct sock *sk, struct ipv6_mc_socklist *iml,
			    struct inet6_dev *idev)
{
	int err;

	/* callers have the socket lock and a write lock on ipv6_sk_mc_lock,
	 * so no other readers or writers of iml or its sflist
	 */
	if (!iml->sflist) {
		/* any-source empty exclude case */
		return ip6_mc_del_src(idev, &iml->addr, iml->sfmode, 0, NULL, 0);
	}
	err = ip6_mc_del_src(idev, &iml->addr, iml->sfmode,
		iml->sflist->sl_count, iml->sflist->sl_addr, 0);
	sock_kfree_s(sk, iml->sflist, IP6_SFLSIZE(iml->sflist->sl_max));
	iml->sflist = NULL;
	return err;
}