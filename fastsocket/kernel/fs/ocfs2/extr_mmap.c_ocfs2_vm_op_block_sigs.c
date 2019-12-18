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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ocfs2_vm_op_block_sigs(sigset_t *blocked, sigset_t *oldset)
{
	/* The best way to deal with signals in the vm path is
	 * to block them upfront, rather than allowing the
	 * locking paths to return -ERESTARTSYS. */
	sigfillset(blocked);

	/* We should technically never get a bad return value
	 * from sigprocmask */
	return sigprocmask(SIG_BLOCK, blocked, oldset);
}