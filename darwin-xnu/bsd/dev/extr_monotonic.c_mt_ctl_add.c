#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_addr_t ;
struct TYPE_7__ {int /*<<< orphan*/  ctr; } ;
struct TYPE_6__ {int /*<<< orphan*/  config; } ;
union monotonic_ctl_add {TYPE_2__ out; TYPE_1__ in; } ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_3__* mt_device_t ;
struct TYPE_8__ {int (* mtd_add ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int copyin (int /*<<< orphan*/ ,union monotonic_ctl_add*,int) ; 
 int copyout (union monotonic_ctl_add*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt_device_assert_lock_held (TYPE_3__*) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mt_ctl_add(mt_device_t dev, user_addr_t uptr)
{
	int error;
	uint32_t ctr;
	union monotonic_ctl_add ctl;

	mt_device_assert_lock_held(dev);

	error = copyin(uptr, &ctl, sizeof(ctl.in));
	if (error) {
		return error;
	}

	error = dev->mtd_add(&ctl.in.config, &ctr);
	if (error) {
		return error;
	}

	ctl.out.ctr = ctr;

	error = copyout(&ctl, uptr, sizeof(ctl.out));
	if (error) {
		return error;
	}

	return 0;
}