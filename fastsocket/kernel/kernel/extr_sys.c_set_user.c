#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct user_struct {int /*<<< orphan*/  processes; } ;
struct cred {struct user_struct* user; int /*<<< orphan*/  uid; } ;
struct TYPE_7__ {TYPE_2__* signal; } ;
struct TYPE_6__ {TYPE_1__* rlim; } ;
struct TYPE_5__ {scalar_t__ rlim_cur; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 struct user_struct* INIT_USER ; 
 size_t RLIMIT_NPROC ; 
 struct user_struct* alloc_uid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  free_uid (struct user_struct*) ; 
 int /*<<< orphan*/  task_can_switch_user (struct user_struct*,TYPE_3__*) ; 

__attribute__((used)) static int set_user(struct cred *new)
{
	struct user_struct *new_user;

	new_user = alloc_uid(current_user_ns(), new->uid);
	if (!new_user)
		return -EAGAIN;

	if (!task_can_switch_user(new_user, current)) {
		free_uid(new_user);
		return -EINVAL;
	}

	if (atomic_read(&new_user->processes) >=
				current->signal->rlim[RLIMIT_NPROC].rlim_cur &&
			new_user != INIT_USER) {
		free_uid(new_user);
		return -EAGAIN;
	}

	free_uid(new->user);
	new->user = new_user;
	return 0;
}