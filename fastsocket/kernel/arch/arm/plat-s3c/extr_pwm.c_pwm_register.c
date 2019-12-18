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
struct pwm_device {int duty_ns; int period_ns; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwm_list ; 
 int /*<<< orphan*/  pwm_lock ; 

__attribute__((used)) static int pwm_register(struct pwm_device *pwm)
{
	pwm->duty_ns = -1;
	pwm->period_ns = -1;

	mutex_lock(&pwm_lock);
	list_add_tail(&pwm->list, &pwm_list);
	mutex_unlock(&pwm_lock);

	return 0;
}