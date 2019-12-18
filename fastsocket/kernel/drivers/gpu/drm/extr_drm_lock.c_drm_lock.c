#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* hw_lock; int /*<<< orphan*/  lock_queue; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  user_waiters; int /*<<< orphan*/  lock_time; struct drm_file* file_priv; } ;
struct drm_master {TYPE_3__ lock; } ;
struct drm_lock {scalar_t__ context; int flags; } ;
struct drm_file {int /*<<< orphan*/  is_master; int /*<<< orphan*/  lock_count; struct drm_master* master; } ;
struct TYPE_8__ {scalar_t__ context; TYPE_1__* lock; } ;
struct drm_device {TYPE_2__* driver; int /*<<< orphan*/  sigmask; TYPE_4__ sigdata; int /*<<< orphan*/ * counts; } ;
struct TYPE_6__ {scalar_t__ (* dma_quiescent ) (struct drm_device*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ DRM_KERNEL_CONTEXT ; 
 int EBUSY ; 
 int EINTR ; 
 int EINVAL ; 
 int /*<<< orphan*/  SIGSTOP ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIGTTIN ; 
 int /*<<< orphan*/  SIGTTOU ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int _DRM_LOCK_QUIESCENT ; 
 size_t _DRM_STAT_LOCKS ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  block_all_signals (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  drm_global_mutex ; 
 scalar_t__ drm_lock_take (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  drm_notifier ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct drm_device*) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 

int drm_lock(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	DECLARE_WAITQUEUE(entry, current);
	struct drm_lock *lock = data;
	struct drm_master *master = file_priv->master;
	int ret = 0;

	++file_priv->lock_count;

	if (lock->context == DRM_KERNEL_CONTEXT) {
		DRM_ERROR("Process %d using kernel context %d\n",
			  task_pid_nr(current), lock->context);
		return -EINVAL;
	}

	DRM_DEBUG("%d (pid %d) requests lock (0x%08x), flags = 0x%08x\n",
		  lock->context, task_pid_nr(current),
		  master->lock.hw_lock->lock, lock->flags);

	add_wait_queue(&master->lock.lock_queue, &entry);
	spin_lock_bh(&master->lock.spinlock);
	master->lock.user_waiters++;
	spin_unlock_bh(&master->lock.spinlock);

	for (;;) {
		__set_current_state(TASK_INTERRUPTIBLE);
		if (!master->lock.hw_lock) {
			/* Device has been unregistered */
			send_sig(SIGTERM, current, 0);
			ret = -EINTR;
			break;
		}
		if (drm_lock_take(&master->lock, lock->context)) {
			master->lock.file_priv = file_priv;
			master->lock.lock_time = jiffies;
			atomic_inc(&dev->counts[_DRM_STAT_LOCKS]);
			break;	/* Got lock */
		}

		/* Contention */
		mutex_unlock(&drm_global_mutex);
		schedule();
		mutex_lock(&drm_global_mutex);
		if (signal_pending(current)) {
			ret = -EINTR;
			break;
		}
	}
	spin_lock_bh(&master->lock.spinlock);
	master->lock.user_waiters--;
	spin_unlock_bh(&master->lock.spinlock);
	__set_current_state(TASK_RUNNING);
	remove_wait_queue(&master->lock.lock_queue, &entry);

	DRM_DEBUG("%d %s\n", lock->context,
		  ret ? "interrupted" : "has lock");
	if (ret) return ret;

	/* don't set the block all signals on the master process for now 
	 * really probably not the correct answer but lets us debug xkb
 	 * xserver for now */
	if (!file_priv->is_master) {
		sigemptyset(&dev->sigmask);
		sigaddset(&dev->sigmask, SIGSTOP);
		sigaddset(&dev->sigmask, SIGTSTP);
		sigaddset(&dev->sigmask, SIGTTIN);
		sigaddset(&dev->sigmask, SIGTTOU);
		dev->sigdata.context = lock->context;
		dev->sigdata.lock = master->lock.hw_lock;
		block_all_signals(drm_notifier, &dev->sigdata, &dev->sigmask);
	}

	if (dev->driver->dma_quiescent && (lock->flags & _DRM_LOCK_QUIESCENT))
	{
		if (dev->driver->dma_quiescent(dev)) {
			DRM_DEBUG("%d waiting for DMA quiescent\n",
				  lock->context);
			return -EBUSY;
		}
	}

	return 0;
}