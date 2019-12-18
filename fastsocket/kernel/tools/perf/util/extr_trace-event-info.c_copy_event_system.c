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
struct dirent {scalar_t__ d_type; char const* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ DT_DIR ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc_or_die (scalar_t__) ; 
 int /*<<< orphan*/  name_in_tp_list (char const*,struct tracepoint_path*) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record_file (char*,int) ; 
 int /*<<< orphan*/  rewinddir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*) ; 
 int stat (char*,struct stat*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  write_or_die (int*,int) ; 

__attribute__((used)) static void copy_event_system(const char *sys, struct tracepoint_path *tps)
{
	struct dirent *dent;
	struct stat st;
	char *format;
	DIR *dir;
	int count = 0;
	int ret;

	dir = opendir(sys);
	if (!dir)
		die("can't read directory '%s'", sys);

	while ((dent = readdir(dir))) {
		if (dent->d_type != DT_DIR ||
		    strcmp(dent->d_name, ".") == 0 ||
		    strcmp(dent->d_name, "..") == 0 ||
		    !name_in_tp_list(dent->d_name, tps))
			continue;
		format = malloc_or_die(strlen(sys) + strlen(dent->d_name) + 10);
		sprintf(format, "%s/%s/format", sys, dent->d_name);
		ret = stat(format, &st);
		free(format);
		if (ret < 0)
			continue;
		count++;
	}

	write_or_die(&count, 4);

	rewinddir(dir);
	while ((dent = readdir(dir))) {
		if (dent->d_type != DT_DIR ||
		    strcmp(dent->d_name, ".") == 0 ||
		    strcmp(dent->d_name, "..") == 0 ||
		    !name_in_tp_list(dent->d_name, tps))
			continue;
		format = malloc_or_die(strlen(sys) + strlen(dent->d_name) + 10);
		sprintf(format, "%s/%s/format", sys, dent->d_name);
		ret = stat(format, &st);

		if (ret >= 0)
			record_file(format, 8);

		free(format);
	}
	closedir(dir);
}