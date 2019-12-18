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
struct inode {int dummy; } ;
struct file {struct apm_user* private_data; } ;
struct apm_user {int suspend_result; int /*<<< orphan*/  suspend_state; int /*<<< orphan*/  writer; int /*<<< orphan*/  suser; } ;

/* Variables and functions */
#define  APM_IOC_SUSPEND 130 
 int EINTR ; 
 int EINVAL ; 
 int EPERM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PM_SUSPEND_MEM ; 
 int /*<<< orphan*/  SUSPEND_ACKED ; 
#define  SUSPEND_ACKTO 129 
 int /*<<< orphan*/  SUSPEND_DONE ; 
 int /*<<< orphan*/  SUSPEND_NONE ; 
#define  SUSPEND_READ 128 
 int /*<<< orphan*/  SUSPEND_WAIT ; 
 int /*<<< orphan*/  apm_suspend_waitqueue ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freezer_count () ; 
 int /*<<< orphan*/  freezer_do_not_count () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_suspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state_lock ; 
 int /*<<< orphan*/  suspend_acks_pending ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
apm_ioctl(struct inode * inode, struct file *filp, u_int cmd, u_long arg)
{
	struct apm_user *as = filp->private_data;
	int err = -EINVAL;

	if (!as->suser || !as->writer)
		return -EPERM;

	switch (cmd) {
	case APM_IOC_SUSPEND:
		mutex_lock(&state_lock);

		as->suspend_result = -EINTR;

		switch (as->suspend_state) {
		case SUSPEND_READ:
			/*
			 * If we read a suspend command from /dev/apm_bios,
			 * then the corresponding APM_IOC_SUSPEND ioctl is
			 * interpreted as an acknowledge.
			 */
			as->suspend_state = SUSPEND_ACKED;
			atomic_dec(&suspend_acks_pending);
			mutex_unlock(&state_lock);

			/*
			 * suspend_acks_pending changed, the notifier needs to
			 * be woken up for this
			 */
			wake_up(&apm_suspend_waitqueue);

			/*
			 * Wait for the suspend/resume to complete.  If there
			 * are pending acknowledges, we wait here for them.
			 */
			freezer_do_not_count();

			wait_event(apm_suspend_waitqueue,
				   as->suspend_state == SUSPEND_DONE);

			/*
			 * Since we are waiting until the suspend is done, the
			 * try_to_freeze() in freezer_count() will not trigger
			 */
			freezer_count();
			break;
		case SUSPEND_ACKTO:
			as->suspend_result = -ETIMEDOUT;
			mutex_unlock(&state_lock);
			break;
		default:
			as->suspend_state = SUSPEND_WAIT;
			mutex_unlock(&state_lock);

			/*
			 * Otherwise it is a request to suspend the system.
			 * Just invoke pm_suspend(), we'll handle it from
			 * there via the notifier.
			 */
			as->suspend_result = pm_suspend(PM_SUSPEND_MEM);
		}

		mutex_lock(&state_lock);
		err = as->suspend_result;
		as->suspend_state = SUSPEND_NONE;
		mutex_unlock(&state_lock);
		break;
	}

	return err;
}