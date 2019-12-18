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
 int MAXPATHLEN ; 
 int add_tracepoint (struct list_head**,int*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strglobmatch (int /*<<< orphan*/ ,char*) ; 
 char* tracing_events_path ; 

__attribute__((used)) static int add_tracepoint_multi_event(struct list_head **list, int *idx,
				      char *sys_name, char *evt_name)
{
	char evt_path[MAXPATHLEN];
	struct dirent *evt_ent;
	DIR *evt_dir;
	int ret = 0;

	snprintf(evt_path, MAXPATHLEN, "%s/%s", tracing_events_path, sys_name);
	evt_dir = opendir(evt_path);
	if (!evt_dir) {
		perror("Can't open event dir");
		return -1;
	}

	while (!ret && (evt_ent = readdir(evt_dir))) {
		if (!strcmp(evt_ent->d_name, ".")
		    || !strcmp(evt_ent->d_name, "..")
		    || !strcmp(evt_ent->d_name, "enable")
		    || !strcmp(evt_ent->d_name, "filter"))
			continue;

		if (!strglobmatch(evt_ent->d_name, evt_name))
			continue;

		ret = add_tracepoint(list, idx, sys_name, evt_ent->d_name);
	}

	return ret;
}