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
typedef  scalar_t__ u8 ;
struct si4713_device {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int si4713_powerdown (struct si4713_device*) ; 
 int si4713_powerup (struct si4713_device*) ; 

__attribute__((used)) static int si4713_set_power_state(struct si4713_device *sdev, u8 value)
{
	int rval;

	mutex_lock(&sdev->mutex);

	if (value)
		rval = si4713_powerup(sdev);
	else
		rval = si4713_powerdown(sdev);

	mutex_unlock(&sdev->mutex);
	return rval;
}