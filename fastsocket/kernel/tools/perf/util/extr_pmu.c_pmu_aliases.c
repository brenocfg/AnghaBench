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
struct stat {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int PATH_MAX ; 
 scalar_t__ pmu_aliases_parse (char*,struct list_head*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* sysfs_find_mountpoint () ; 

__attribute__((used)) static int pmu_aliases(char *name, struct list_head *head)
{
	struct stat st;
	char path[PATH_MAX];
	const char *sysfs;

	sysfs = sysfs_find_mountpoint();
	if (!sysfs)
		return -1;

	snprintf(path, PATH_MAX,
		 "%s/bus/event_source/devices/%s/events", sysfs, name);

	if (stat(path, &st) < 0)
		return 0;	 /* no error if 'events' does not exist */

	if (pmu_aliases_parse(path, head))
		return -1;

	return 0;
}