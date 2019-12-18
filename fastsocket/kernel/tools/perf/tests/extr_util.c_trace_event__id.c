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
typedef  int /*<<< orphan*/  id ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ,char const*) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,char*,int) ; 
 int /*<<< orphan*/  tracing_events_path ; 

int trace_event__id(const char *evname)
{
	char *filename;
	int err = -1, fd;

	if (asprintf(&filename,
		     "%s/syscalls/%s/id",
		     tracing_events_path, evname) < 0)
		return -1;

	fd = open(filename, O_RDONLY);
	if (fd >= 0) {
		char id[16];
		if (read(fd, id, sizeof(id)) > 0)
			err = atoi(id);
		close(fd);
	}

	free(filename);
	return err;
}