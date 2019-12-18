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
 int /*<<< orphan*/  sysfs_notify_dirent (struct sysfs_dirent*) ; 

__attribute__((used)) static inline void sysfs_notify_dirent_safe(struct sysfs_dirent *sd)
{
	if (sd)
		sysfs_notify_dirent(sd);
}