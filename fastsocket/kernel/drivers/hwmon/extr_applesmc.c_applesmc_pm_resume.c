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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_KEY ; 
 scalar_t__ applesmc_light ; 
 int /*<<< orphan*/  applesmc_lock ; 
 int /*<<< orphan*/  applesmc_write_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  backlight_state ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int applesmc_pm_resume(struct device *dev)
{
	mutex_lock(&applesmc_lock);
	if (applesmc_light)
		applesmc_write_key(BACKLIGHT_KEY, backlight_state, 2);
	mutex_unlock(&applesmc_lock);
	return 0;
}