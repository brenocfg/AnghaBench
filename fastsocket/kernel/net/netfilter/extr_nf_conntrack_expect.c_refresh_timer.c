#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nf_conntrack_expect_policy {int timeout; } ;
struct TYPE_5__ {scalar_t__ expires; } ;
struct nf_conntrack_expect {size_t class; TYPE_2__ timeout; int /*<<< orphan*/  master; } ;
struct nf_conn_help {TYPE_1__* helper; } ;
struct TYPE_4__ {struct nf_conntrack_expect_policy* expect_policy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 struct nf_conn_help* nfct_help (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int refresh_timer(struct nf_conntrack_expect *i)
{
	struct nf_conn_help *master_help = nfct_help(i->master);
	const struct nf_conntrack_expect_policy *p;

	if (!del_timer(&i->timeout))
		return 0;

	p = &master_help->helper->expect_policy[i->class];
	i->timeout.expires = jiffies + p->timeout * HZ;
	add_timer(&i->timeout);
	return 1;
}