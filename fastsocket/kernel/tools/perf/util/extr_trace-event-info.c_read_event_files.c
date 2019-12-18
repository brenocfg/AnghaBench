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
struct tracepoint_path {int dummy; } ;
struct stat {int dummy; } ;
struct dirent {scalar_t__ d_type; char* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ DT_DIR ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_event_system (char*,struct tracepoint_path*) ; 
 int /*<<< orphan*/  die (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_tracing_file (char*) ; 
 char* malloc_or_die (int) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  put_tracing_file (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewinddir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int stat (char*,struct stat*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  system_in_tp_list (char*,struct tracepoint_path*) ; 
 int /*<<< orphan*/  write_or_die (int*,int) ; 

__attribute__((used)) static void read_event_files(struct tracepoint_path *tps)
{
	struct dirent *dent;
	struct stat st;
	char *path;
	char *sys;
	DIR *dir;
	int count = 0;
	int ret;

	path = get_tracing_file("events");

	dir = opendir(path);
	if (!dir)
		die("can't read directory '%s'", path);

	while ((dent = readdir(dir))) {
		if (dent->d_type != DT_DIR ||
		    strcmp(dent->d_name, ".") == 0 ||
		    strcmp(dent->d_name, "..") == 0 ||
		    strcmp(dent->d_name, "ftrace") == 0 ||
		    !system_in_tp_list(dent->d_name, tps))
			continue;
		count++;
	}

	write_or_die(&count, 4);

	rewinddir(dir);
	while ((dent = readdir(dir))) {
		if (dent->d_type != DT_DIR ||
		    strcmp(dent->d_name, ".") == 0 ||
		    strcmp(dent->d_name, "..") == 0 ||
		    strcmp(dent->d_name, "ftrace") == 0 ||
		    !system_in_tp_list(dent->d_name, tps))
			continue;
		sys = malloc_or_die(strlen(path) + strlen(dent->d_name) + 2);
		sprintf(sys, "%s/%s", path, dent->d_name);
		ret = stat(sys, &st);
		if (ret >= 0) {
			write_or_die(dent->d_name, strlen(dent->d_name) + 1);
			copy_event_system(sys, tps);
		}
		free(sys);
	}

	closedir(dir);
	put_tracing_file(path);
}