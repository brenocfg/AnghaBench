#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* work_interval_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct work_interval_create_params {int /*<<< orphan*/  wicp_port; int /*<<< orphan*/  wicp_create_flags; int /*<<< orphan*/  wicp_id; } ;
typedef  int /*<<< orphan*/  create_params ;
struct TYPE_4__ {int /*<<< orphan*/  wi_port; int /*<<< orphan*/  create_flags; int /*<<< orphan*/  work_interval_id; int /*<<< orphan*/  thread_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  WORK_INTERVAL_OPERATION_CREATE2 ; 
 int /*<<< orphan*/  __thread_selfid () ; 
 int __work_interval_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct work_interval_create_params*,int) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_1__* malloc (int) ; 

int
work_interval_create(work_interval_t *interval_handle, uint32_t create_flags)
{
	int ret;
	work_interval_t handle;

	if (interval_handle == NULL) {
		errno = EINVAL;
		return -1;
	}

	struct work_interval_create_params create_params = {
		.wicp_create_flags = create_flags,
	};

	ret = __work_interval_ctl(WORK_INTERVAL_OPERATION_CREATE2, 0,
	                          &create_params, sizeof(create_params));
	if (ret == -1) {
		return ret;
	}

	handle = malloc(sizeof(*handle));
	if (handle == NULL) {
		errno = ENOMEM;
		return -1;
	}

	handle->thread_id = __thread_selfid();
	handle->work_interval_id = create_params.wicp_id;
	handle->create_flags = create_params.wicp_create_flags;
	handle->wi_port = create_params.wicp_port;

	*interval_handle = handle;
	return 0;
}