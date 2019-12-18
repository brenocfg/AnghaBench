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
struct linux_binprm {scalar_t__ interp; scalar_t__ filename; scalar_t__ cred; } ;
struct TYPE_2__ {int /*<<< orphan*/  cred_guard_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort_creds (scalar_t__) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  free_arg_pages (struct linux_binprm*) ; 
 int /*<<< orphan*/  kfree (struct linux_binprm*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void free_bprm(struct linux_binprm *bprm)
{
	free_arg_pages(bprm);
	if (bprm->cred) {
		mutex_unlock(&current->cred_guard_mutex);
		abort_creds(bprm->cred);
	}
	/* If a binfmt changed the interp, free it. */
	if (bprm->interp != bprm->filename)
		kfree(bprm->interp);
	kfree(bprm);
}