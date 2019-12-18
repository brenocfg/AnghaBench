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
struct sysfs_dirent {int dummy; } ;

/* Variables and functions */
 struct sysfs_dirent* sysfs_get_dirent (struct sysfs_dirent*,char*) ; 

__attribute__((used)) static inline struct sysfs_dirent *sysfs_get_dirent_safe(struct sysfs_dirent *sd, char *name)
{
	if (sd)
		return sysfs_get_dirent(sd, name);
	return sd;
}