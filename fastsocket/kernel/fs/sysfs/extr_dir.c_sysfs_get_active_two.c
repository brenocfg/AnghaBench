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
struct sysfs_dirent {struct sysfs_dirent* s_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  sysfs_get_active (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_put_active (struct sysfs_dirent*) ; 
 scalar_t__ unlikely (int) ; 

struct sysfs_dirent *sysfs_get_active_two(struct sysfs_dirent *sd)
{
	if (sd) {
		if (sd->s_parent && unlikely(!sysfs_get_active(sd->s_parent)))
			return NULL;
		if (unlikely(!sysfs_get_active(sd))) {
			sysfs_put_active(sd->s_parent);
			return NULL;
		}
	}
	return sd;
}