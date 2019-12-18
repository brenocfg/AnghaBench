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
struct ipv6_pinfo {struct ipv6_fl_socklist* ipv6_fl_list; } ;
struct ipv6_fl_socklist {struct ip6_flowlabel* fl; struct ipv6_fl_socklist* next; } ;
struct ip6_flowlabel {int /*<<< orphan*/  users; int /*<<< orphan*/  lastuse; int /*<<< orphan*/  label; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  IPV6_FLOWLABEL_MASK ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 int /*<<< orphan*/  ip6_sk_fl_lock ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

struct ip6_flowlabel * fl6_sock_lookup(struct sock *sk, __be32 label)
{
	struct ipv6_fl_socklist *sfl;
	struct ipv6_pinfo *np = inet6_sk(sk);

	label &= IPV6_FLOWLABEL_MASK;

	read_lock_bh(&ip6_sk_fl_lock);
	for (sfl=np->ipv6_fl_list; sfl; sfl = sfl->next) {
		struct ip6_flowlabel *fl = sfl->fl;
		if (fl->label == label) {
			fl->lastuse = jiffies;
			atomic_inc(&fl->users);
			read_unlock_bh(&ip6_sk_fl_lock);
			return fl;
		}
	}
	read_unlock_bh(&ip6_sk_fl_lock);
	return NULL;
}