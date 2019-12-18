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
struct mddev {int safemode; int /*<<< orphan*/  thread; int /*<<< orphan*/  sysfs_state; scalar_t__ external; int /*<<< orphan*/  writes_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_notify_dirent_safe (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void md_safemode_timeout(unsigned long data)
{
	struct mddev *mddev = (struct mddev *) data;

	if (!atomic_read(&mddev->writes_pending)) {
		mddev->safemode = 1;
		if (mddev->external)
			sysfs_notify_dirent_safe(mddev->sysfs_state);
	}
	md_wakeup_thread(mddev->thread);
}