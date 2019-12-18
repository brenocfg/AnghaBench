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
struct subprocess_info {char* path; int wait; int retval; int /*<<< orphan*/ * complete; int /*<<< orphan*/  work; TYPE_1__* cred; } ;
typedef  enum umh_wait { ____Placeholder_umh_wait } umh_wait ;
struct TYPE_2__ {int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int UMH_KILLABLE ; 
 int UMH_NO_WAIT ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_usermodehelper_freeinfo (struct subprocess_info*) ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  helper_lock () ; 
 int /*<<< orphan*/  helper_unlock () ; 
 int /*<<< orphan*/  khelper_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ usermodehelper_disabled ; 
 int /*<<< orphan*/  validate_creds (TYPE_1__*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int wait_for_completion_killable (int /*<<< orphan*/ *) ; 
 scalar_t__ xchg (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int call_usermodehelper_exec(struct subprocess_info *sub_info,
			     enum umh_wait wait)
{
	DECLARE_COMPLETION_ONSTACK(done);
	int retval = 0;

	BUG_ON(atomic_read(&sub_info->cred->usage) != 1);
	validate_creds(sub_info->cred);

	helper_lock();
	if (sub_info->path[0] == '\0')
		goto out;

	if (!khelper_wq || usermodehelper_disabled) {
		retval = -EBUSY;
		goto out;
	}

	sub_info->complete = &done;
	sub_info->wait = wait;

	queue_work(khelper_wq, &sub_info->work);
	if (wait == UMH_NO_WAIT)	/* task has freed sub_info */
		goto unlock;

	if (wait & UMH_KILLABLE) {
		retval = wait_for_completion_killable(&done);
		if (!retval)
			goto wait_done;

		/* umh_complete() will see NULL and free sub_info */
		if (xchg(&sub_info->complete, NULL))
			goto unlock;
		/* fallthrough, umh_complete() was already called */
	}

	wait_for_completion(&done);
wait_done:
	retval = sub_info->retval;
out:
	call_usermodehelper_freeinfo(sub_info);
unlock:
	helper_unlock();
	return retval;
}