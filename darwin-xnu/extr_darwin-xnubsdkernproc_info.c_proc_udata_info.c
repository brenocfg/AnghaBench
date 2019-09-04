#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int uint32_t ;
typedef  TYPE_1__* proc_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_5__ {scalar_t__ p_pid; int /*<<< orphan*/  p_user_data; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int ENOTSUP ; 
 int ESRCH ; 
 TYPE_1__* PROC_NULL ; 
#define  PROC_UDATA_INFO_GET 129 
#define  PROC_UDATA_INFO_SET 128 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* proc_find (int) ; 
 int /*<<< orphan*/  proc_rele (TYPE_1__*) ; 
 scalar_t__ proc_selfpid () ; 

int
proc_udata_info(int pid, int flavor, user_addr_t buffer, uint32_t bufsize, int32_t *retval)
{
	int err = 0;
	proc_t p;

	p = proc_find(pid);
	if (p == PROC_NULL) {
		return ESRCH;
	}

	/*
	 * Only support calls against oneself for the moment.
	 */
	if (p->p_pid != proc_selfpid()) {
		err = EACCES;
		goto out;
	}

	if (bufsize != sizeof (p->p_user_data)) {
		err = EINVAL;
		goto out;
	}

	switch (flavor) {
	case PROC_UDATA_INFO_SET:
		err = copyin(buffer, &p->p_user_data, sizeof (p->p_user_data));
		break;
	case PROC_UDATA_INFO_GET:
		err = copyout(&p->p_user_data, buffer, sizeof (p->p_user_data));
		break;
	default:
		err = ENOTSUP;
		break;
	}

out:
	proc_rele(p);

	if (err == 0) {
		*retval = 0;
	}

	return err;
}