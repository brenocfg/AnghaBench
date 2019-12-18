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
struct TYPE_2__ {int /*<<< orphan*/  (* stop ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ op_arm_enabled ; 
 TYPE_1__* op_arm_model ; 
 int /*<<< orphan*/  op_arm_mutex ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void op_arm_stop(void)
{
	mutex_lock(&op_arm_mutex);
	if (op_arm_enabled)
		op_arm_model->stop();
	op_arm_enabled = 0;
	mutex_unlock(&op_arm_mutex);
}