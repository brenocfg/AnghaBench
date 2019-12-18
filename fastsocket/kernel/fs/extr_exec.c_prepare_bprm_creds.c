#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct linux_binprm {int /*<<< orphan*/  cred; } ;
struct TYPE_2__ {int /*<<< orphan*/  cred_guard_mutex; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ERESTARTNOINTR ; 
 TYPE_1__* current ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_exec_creds () ; 

int prepare_bprm_creds(struct linux_binprm *bprm)
{
	if (mutex_lock_interruptible(&current->cred_guard_mutex))
		return -ERESTARTNOINTR;

	bprm->cred = prepare_exec_creds();
	if (likely(bprm->cred))
		return 0;

	mutex_unlock(&current->cred_guard_mutex);
	return -ENOMEM;
}