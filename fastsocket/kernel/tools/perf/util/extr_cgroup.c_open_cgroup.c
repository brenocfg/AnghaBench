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

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int PATH_MAX ; 
 scalar_t__ cgroupfs_find_mountpoint (char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int open_cgroup(char *name)
{
	char path[PATH_MAX + 1];
	char mnt[PATH_MAX + 1];
	int fd;


	if (cgroupfs_find_mountpoint(mnt, PATH_MAX + 1))
		return -1;

	snprintf(path, PATH_MAX, "%s/%s", mnt, name);

	fd = open(path, O_RDONLY);
	if (fd == -1)
		fprintf(stderr, "no access to cgroup %s\n", path);

	return fd;
}