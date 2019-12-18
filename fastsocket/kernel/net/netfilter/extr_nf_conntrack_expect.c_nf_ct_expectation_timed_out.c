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
struct nf_conntrack_expect {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_conntrack_lock ; 
 int /*<<< orphan*/  nf_ct_expect_put (struct nf_conntrack_expect*) ; 
 int /*<<< orphan*/  nf_ct_unlink_expect (struct nf_conntrack_expect*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nf_ct_expectation_timed_out(unsigned long ul_expect)
{
	struct nf_conntrack_expect *exp = (void *)ul_expect;

	spin_lock_bh(&nf_conntrack_lock);
	nf_ct_unlink_expect(exp);
	spin_unlock_bh(&nf_conntrack_lock);
	nf_ct_expect_put(exp);
}