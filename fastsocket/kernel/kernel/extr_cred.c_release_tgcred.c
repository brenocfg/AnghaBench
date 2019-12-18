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
struct thread_group_cred {int /*<<< orphan*/  rcu; int /*<<< orphan*/  usage; } ;
struct cred {struct thread_group_cred* tgcred; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_tgcred_rcu ; 

__attribute__((used)) static void release_tgcred(struct cred *cred)
{
#ifdef CONFIG_KEYS
	struct thread_group_cred *tgcred = cred->tgcred;

	if (atomic_dec_and_test(&tgcred->usage))
		call_rcu(&tgcred->rcu, release_tgcred_rcu);
#endif
}