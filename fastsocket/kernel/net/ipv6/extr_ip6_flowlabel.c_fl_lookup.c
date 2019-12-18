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
struct net {int dummy; } ;
struct ip6_flowlabel {int /*<<< orphan*/  users; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 struct ip6_flowlabel* __fl_lookup (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip6_fl_lock ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ip6_flowlabel *fl_lookup(struct net *net, __be32 label)
{
	struct ip6_flowlabel *fl;

	read_lock_bh(&ip6_fl_lock);
	fl = __fl_lookup(net, label);
	if (fl)
		atomic_inc(&fl->users);
	read_unlock_bh(&ip6_fl_lock);
	return fl;
}