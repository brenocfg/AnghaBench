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
struct wdm_device {TYPE_1__* intf; int /*<<< orphan*/  flags; int /*<<< orphan*/  count; int /*<<< orphan*/  plock; } ;
struct inode {int dummy; } ;
struct file {struct wdm_device* private_data; } ;
struct TYPE_2__ {scalar_t__ needs_remote_wakeup; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WDM_DISCONNECTING ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kill_urbs (struct wdm_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdm_mutex ; 

__attribute__((used)) static int wdm_release(struct inode *inode, struct file *file)
{
	struct wdm_device *desc = file->private_data;

	mutex_lock(&wdm_mutex);
	mutex_lock(&desc->plock);
	desc->count--;
	mutex_unlock(&desc->plock);

	if (!desc->count) {
		dev_dbg(&desc->intf->dev, "wdm_release: cleanup");
		kill_urbs(desc);
		if (!test_bit(WDM_DISCONNECTING, &desc->flags))
			desc->intf->needs_remote_wakeup = 0;
	}
	mutex_unlock(&wdm_mutex);
	return 0;
}