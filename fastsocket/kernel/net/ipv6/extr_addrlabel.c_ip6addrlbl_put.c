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
struct ip6addrlbl_entry {int /*<<< orphan*/  rcu; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6addrlbl_free_rcu ; 

__attribute__((used)) static inline void ip6addrlbl_put(struct ip6addrlbl_entry *p)
{
	if (atomic_dec_and_test(&p->refcnt))
		call_rcu(&p->rcu, ip6addrlbl_free_rcu);
}