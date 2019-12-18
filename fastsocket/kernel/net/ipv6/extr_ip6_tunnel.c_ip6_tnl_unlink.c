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
struct ip6_tnl_net {int dummy; } ;
struct ip6_tnl {struct ip6_tnl* next; int /*<<< orphan*/  parms; } ;

/* Variables and functions */
 struct ip6_tnl** ip6_tnl_bucket (struct ip6_tnl_net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip6_tnl_lock ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ip6_tnl_unlink(struct ip6_tnl_net *ip6n, struct ip6_tnl *t)
{
	struct ip6_tnl **tp;

	for (tp = ip6_tnl_bucket(ip6n, &t->parms); *tp; tp = &(*tp)->next) {
		if (t == *tp) {
			write_lock_bh(&ip6_tnl_lock);
			*tp = t->next;
			write_unlock_bh(&ip6_tnl_lock);
			break;
		}
	}
}