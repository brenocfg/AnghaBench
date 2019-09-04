#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* work_interval_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct work_interval_notification {int /*<<< orphan*/  create_flags; int /*<<< orphan*/  notify_flags; int /*<<< orphan*/  next_start; int /*<<< orphan*/  deadline; int /*<<< orphan*/  finish; int /*<<< orphan*/  start; } ;
typedef  int /*<<< orphan*/  notification ;
struct TYPE_3__ {int /*<<< orphan*/  work_interval_id; int /*<<< orphan*/  create_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  WORK_INTERVAL_OPERATION_NOTIFY ; 
 int __work_interval_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct work_interval_notification*,int) ; 
 int /*<<< orphan*/  errno ; 

int
work_interval_notify(work_interval_t interval_handle, uint64_t start,
                     uint64_t finish, uint64_t deadline, uint64_t next_start,
                     uint32_t notify_flags)
{
	int ret;
	uint64_t work_interval_id;
	struct work_interval_notification notification = {
		.start = start,
		.finish = finish,
		.deadline = deadline,
		.next_start = next_start,
		.notify_flags = notify_flags
	};

	if (interval_handle == NULL) {
		errno = EINVAL;
		return -1;
	}

	notification.create_flags = interval_handle->create_flags;
	work_interval_id = interval_handle->work_interval_id;

	ret = __work_interval_ctl(WORK_INTERVAL_OPERATION_NOTIFY, work_interval_id,
	                          &notification, sizeof(notification));
	return ret;
}