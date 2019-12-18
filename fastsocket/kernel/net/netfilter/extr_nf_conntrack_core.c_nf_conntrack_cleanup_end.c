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

/* Variables and functions */
 int /*<<< orphan*/  nf_conntrack_cleanup_init_net () ; 
 int /*<<< orphan*/  nf_ct_destroy ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nf_conntrack_cleanup_end(void)
{
	rcu_assign_pointer(nf_ct_destroy, NULL);
	nf_conntrack_cleanup_init_net();
}