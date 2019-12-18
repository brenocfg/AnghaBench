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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  FANS_COUNT ; 
 int /*<<< orphan*/  applesmc_lock ; 
 int applesmc_read_key (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int applesmc_get_fan_count(void)
{
	int ret;
	u8 buffer[1];

	mutex_lock(&applesmc_lock);

	ret = applesmc_read_key(FANS_COUNT, buffer, 1);

	mutex_unlock(&applesmc_lock);
	if (ret)
		return ret;
	else
		return buffer[0];
}