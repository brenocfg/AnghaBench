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
struct mddev {int sync_speed_min; } ;

/* Variables and functions */
 int sysctl_speed_limit_min ; 

__attribute__((used)) static inline int speed_min(struct mddev *mddev)
{
	return mddev->sync_speed_min ?
		mddev->sync_speed_min : sysctl_speed_limit_min;
}