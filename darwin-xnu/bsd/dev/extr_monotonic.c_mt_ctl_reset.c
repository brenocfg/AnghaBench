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
typedef  TYPE_1__* mt_device_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* mtd_reset ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mt_device_assert_lock_held (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static int
mt_ctl_reset(mt_device_t dev)
{
	mt_device_assert_lock_held(dev);
	dev->mtd_reset();
	return 0;
}