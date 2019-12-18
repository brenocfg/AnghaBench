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
struct test__event_st {char* name; int /*<<< orphan*/  check; } ;
struct stat {int dummy; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int MAX_NAME ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* sysfs_find_mountpoint () ; 
 int /*<<< orphan*/  test__checkevent_pmu_events ; 
 int test_event (struct test__event_st*) ; 

__attribute__((used)) static int test_pmu_events(void)
{
	struct stat st;
	char path[PATH_MAX];
	struct dirent *ent;
	DIR *dir;
	int ret;

	snprintf(path, PATH_MAX, "%s/bus/event_source/devices/cpu/events/",
		 sysfs_find_mountpoint());

	ret = stat(path, &st);
	if (ret) {
		pr_debug("ommiting PMU cpu events tests\n");
		return 0;
	}

	dir = opendir(path);
	if (!dir) {
		pr_debug("can't open pmu event dir");
		return -1;
	}

	while (!ret && (ent = readdir(dir))) {
#define MAX_NAME 100
		struct test__event_st e;
		char name[MAX_NAME];

		if (!strcmp(ent->d_name, ".") ||
		    !strcmp(ent->d_name, ".."))
			continue;

		snprintf(name, MAX_NAME, "cpu/event=%s/u", ent->d_name);

		e.name  = name;
		e.check = test__checkevent_pmu_events;

		ret = test_event(&e);
#undef MAX_NAME
	}

	closedir(dir);
	return ret;
}