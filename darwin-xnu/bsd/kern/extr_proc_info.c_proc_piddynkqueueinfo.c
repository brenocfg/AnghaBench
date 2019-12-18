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
typedef  scalar_t__ user_addr_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ proc_t ;
typedef  int /*<<< orphan*/  kqueue_id_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_SAME_USER ; 
 int EFAULT ; 
 int ENOTSUP ; 
 int ESRCH ; 
 int /*<<< orphan*/  PROC_INFO_CALL_PIDDYNKQUEUEINFO ; 
 scalar_t__ PROC_NULL ; 
#define  PROC_PIDDYNKQUEUE_EXTINFO 129 
#define  PROC_PIDDYNKQUEUE_INFO 128 
 scalar_t__ USER_ADDR_NULL ; 
 int kevent_copyout_dynkqextinfo (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int kevent_copyout_dynkqinfo (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ proc_find (int) ; 
 int /*<<< orphan*/  proc_rele (scalar_t__) ; 
 int proc_security_policy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
proc_piddynkqueueinfo(int pid, int flavor, kqueue_id_t kq_id,
		user_addr_t ubuf, uint32_t bufsize, int32_t *retval)
{
	proc_t p;
	int err;

	if (ubuf == USER_ADDR_NULL) {
		return EFAULT;
	}

	p = proc_find(pid);
	if (p == PROC_NULL) {
		return ESRCH;
	}

	err = proc_security_policy(p, PROC_INFO_CALL_PIDDYNKQUEUEINFO, 0, CHECK_SAME_USER);
	if (err) {
		goto out;
	}

	switch (flavor) {
	case PROC_PIDDYNKQUEUE_INFO:
		err = kevent_copyout_dynkqinfo(p, kq_id, ubuf, bufsize, retval);
		break;
	case PROC_PIDDYNKQUEUE_EXTINFO:
		err = kevent_copyout_dynkqextinfo(p, kq_id, ubuf, bufsize, retval);
		break;
	default:
		err = ENOTSUP;
		break;
	}

out:
	proc_rele(p);

	return err;
}