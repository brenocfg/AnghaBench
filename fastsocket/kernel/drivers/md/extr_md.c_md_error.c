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
struct TYPE_4__ {scalar_t__ func; } ;
struct mddev {TYPE_2__ event_work; int /*<<< orphan*/  thread; int /*<<< orphan*/  recovery; scalar_t__ degraded; TYPE_1__* pers; } ;
struct md_rdev {int /*<<< orphan*/  sysfs_state; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* error_handler ) (struct mddev*,struct md_rdev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  MD_BUG () ; 
 int /*<<< orphan*/  MD_RECOVERY_INTR ; 
 int /*<<< orphan*/  MD_RECOVERY_NEEDED ; 
 int /*<<< orphan*/  MD_RECOVERY_RECOVER ; 
 int /*<<< orphan*/  md_misc_wq ; 
 int /*<<< orphan*/  md_new_event_inintr (struct mddev*) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mddev*,struct md_rdev*) ; 
 int /*<<< orphan*/  sysfs_notify_dirent_safe (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void md_error(struct mddev *mddev, struct md_rdev *rdev)
{
	if (!mddev) {
		MD_BUG();
		return;
	}

	if (!rdev || test_bit(Faulty, &rdev->flags))
		return;

	if (!mddev->pers || !mddev->pers->error_handler)
		return;
	mddev->pers->error_handler(mddev,rdev);
	if (mddev->degraded)
		set_bit(MD_RECOVERY_RECOVER, &mddev->recovery);
	sysfs_notify_dirent_safe(rdev->sysfs_state);
	set_bit(MD_RECOVERY_INTR, &mddev->recovery);
	set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
	md_wakeup_thread(mddev->thread);
	if (mddev->event_work.func)
		queue_work(md_misc_wq, &mddev->event_work);
	md_new_event_inintr(mddev);
}