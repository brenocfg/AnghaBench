#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct watchdog_device {unsigned int max_timeout; unsigned int min_timeout; int /*<<< orphan*/  lock; TYPE_1__* ops; int /*<<< orphan*/  status; TYPE_2__* info; } ;
struct TYPE_4__ {int options; } ;
struct TYPE_3__ {int (* set_timeout ) (struct watchdog_device*,unsigned int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int WDIOF_SETTIMEOUT ; 
 int /*<<< orphan*/  WDOG_UNREGISTERED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct watchdog_device*,unsigned int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int watchdog_set_timeout(struct watchdog_device *wddev,
							unsigned int timeout)
{
	int err;

	if ((wddev->ops->set_timeout == NULL) ||
	    !(wddev->info->options & WDIOF_SETTIMEOUT))
		return -EOPNOTSUPP;

	if ((wddev->max_timeout != 0) &&
	    (timeout < wddev->min_timeout || timeout > wddev->max_timeout))
		return -EINVAL;

	mutex_lock(&wddev->lock);

	if (test_bit(WDOG_UNREGISTERED, &wddev->status)) {
		err = -ENODEV;
		goto out_timeout;
	}

	err = wddev->ops->set_timeout(wddev, timeout);

out_timeout:
	mutex_unlock(&wddev->lock);
	return err;
}