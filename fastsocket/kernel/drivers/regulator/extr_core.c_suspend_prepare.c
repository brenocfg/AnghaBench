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
typedef  int suspend_state_t ;
struct regulator_dev {TYPE_1__* constraints; } ;
struct TYPE_2__ {int /*<<< orphan*/  state_disk; int /*<<< orphan*/  state_mem; int /*<<< orphan*/  state_standby; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PM_SUSPEND_MAX 130 
#define  PM_SUSPEND_MEM 129 
#define  PM_SUSPEND_STANDBY 128 
 int suspend_set_state (struct regulator_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int suspend_prepare(struct regulator_dev *rdev, suspend_state_t state)
{
	if (!rdev->constraints)
		return -EINVAL;

	switch (state) {
	case PM_SUSPEND_STANDBY:
		return suspend_set_state(rdev,
			&rdev->constraints->state_standby);
	case PM_SUSPEND_MEM:
		return suspend_set_state(rdev,
			&rdev->constraints->state_mem);
	case PM_SUSPEND_MAX:
		return suspend_set_state(rdev,
			&rdev->constraints->state_disk);
	default:
		return -EINVAL;
	}
}