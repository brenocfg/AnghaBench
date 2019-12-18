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
typedef  int /*<<< orphan*/  u32 ;
struct nf_conntrack_expect {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPEXP_NEW ; 
 int __nf_ct_expect_check (struct nf_conntrack_expect*) ; 
 int /*<<< orphan*/  nf_conntrack_lock ; 
 int /*<<< orphan*/  nf_ct_expect_event_report (int /*<<< orphan*/ ,struct nf_conntrack_expect*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nf_ct_expect_insert (struct nf_conntrack_expect*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int nf_ct_expect_related_report(struct nf_conntrack_expect *expect, 
				u32 pid, int report)
{
	int ret;

	spin_lock_bh(&nf_conntrack_lock);
	ret = __nf_ct_expect_check(expect);
	if (ret <= 0)
		goto out;

	ret = 0;
	nf_ct_expect_insert(expect);
	spin_unlock_bh(&nf_conntrack_lock);
	nf_ct_expect_event_report(IPEXP_NEW, expect, pid, report);
	return ret;
out:
	spin_unlock_bh(&nf_conntrack_lock);
	return ret;
}