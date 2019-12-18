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
struct TYPE_2__ {int (* setup_ctrs ) () ;} ;

/* Variables and functions */
 TYPE_1__* op_arm_model ; 
 int /*<<< orphan*/  oprofilefs_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 () ; 

__attribute__((used)) static int op_arm_setup(void)
{
	int ret;

	spin_lock(&oprofilefs_lock);
	ret = op_arm_model->setup_ctrs();
	spin_unlock(&oprofilefs_lock);
	return ret;
}