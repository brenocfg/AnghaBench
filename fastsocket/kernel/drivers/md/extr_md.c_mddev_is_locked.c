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
struct mddev {int /*<<< orphan*/  reconfig_mutex; } ;

/* Variables and functions */
 int mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int mddev_is_locked(struct mddev *mddev)
{
	return mutex_is_locked(&mddev->reconfig_mutex);
}