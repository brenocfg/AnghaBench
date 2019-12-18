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
struct list_head {int dummy; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int add_tracepoint_event (struct list_head**,int*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strglobmatch (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tracing_events_path ; 

__attribute__((used)) static int add_tracepoint_multi_sys(struct list_head **list, int *idx,
				    char *sys_name, char *evt_name)
{
	struct dirent *events_ent;
	DIR *events_dir;
	int ret = 0;

	events_dir = opendir(tracing_events_path);
	if (!events_dir) {
		perror("Can't open event dir");
		return -1;
	}

	while (!ret && (events_ent = readdir(events_dir))) {
		if (!strcmp(events_ent->d_name, ".")
		    || !strcmp(events_ent->d_name, "..")
		    || !strcmp(events_ent->d_name, "enable")
		    || !strcmp(events_ent->d_name, "header_event")
		    || !strcmp(events_ent->d_name, "header_page"))
			continue;

		if (!strglobmatch(events_ent->d_name, sys_name))
			continue;

		ret = add_tracepoint_event(list, idx, events_ent->d_name,
					   evt_name);
	}

	closedir(events_dir);
	return ret;
}