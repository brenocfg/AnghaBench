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
typedef  int /*<<< orphan*/  u_long ;
typedef  int u_int ;
struct file {struct apm_user* private_data; } ;
struct apm_user {int suspend_wait; int suspend_result; int /*<<< orphan*/  suspends_pending; int /*<<< orphan*/  suspends_read; int /*<<< orphan*/  standbys_pending; int /*<<< orphan*/  standbys_read; int /*<<< orphan*/  writer; int /*<<< orphan*/  suser; } ;

/* Variables and functions */
#define  APM_IOC_STANDBY 129 
#define  APM_IOC_SUSPEND 128 
 int /*<<< orphan*/  APM_USER_STANDBY ; 
 int /*<<< orphan*/  APM_USER_SUSPEND ; 
 long EIO ; 
 long ENOTTY ; 
 long EPERM ; 
 int /*<<< orphan*/  apm_suspend_waitqueue ; 
 scalar_t__ check_apm_user (struct apm_user*,char*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  queue_event (int /*<<< orphan*/ ,struct apm_user*) ; 
 int /*<<< orphan*/  standby () ; 
 int /*<<< orphan*/  standbys_pending ; 
 int suspend (int) ; 
 int /*<<< orphan*/  suspends_pending ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static long do_ioctl(struct file *filp, u_int cmd, u_long arg)
{
	struct apm_user *as;
	int ret;

	as = filp->private_data;
	if (check_apm_user(as, "ioctl"))
		return -EIO;
	if (!as->suser || !as->writer)
		return -EPERM;
	switch (cmd) {
	case APM_IOC_STANDBY:
		lock_kernel();
		if (as->standbys_read > 0) {
			as->standbys_read--;
			as->standbys_pending--;
			standbys_pending--;
		} else
			queue_event(APM_USER_STANDBY, as);
		if (standbys_pending <= 0)
			standby();
		unlock_kernel();
		break;
	case APM_IOC_SUSPEND:
		lock_kernel();
		if (as->suspends_read > 0) {
			as->suspends_read--;
			as->suspends_pending--;
			suspends_pending--;
		} else
			queue_event(APM_USER_SUSPEND, as);
		if (suspends_pending <= 0) {
			ret = suspend(1);
		} else {
			as->suspend_wait = 1;
			wait_event_interruptible(apm_suspend_waitqueue,
					as->suspend_wait == 0);
			ret = as->suspend_result;
		}
		unlock_kernel();
		return ret;
	default:
		return -ENOTTY;
	}
	return 0;
}