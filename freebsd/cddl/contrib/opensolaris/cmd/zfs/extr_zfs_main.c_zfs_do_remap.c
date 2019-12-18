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
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 int optopt ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 int zfs_remap_indirects (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
zfs_do_remap(int argc, char **argv)
{
	const char *fsname;
	int err = 0;
	int c;

	/* check options */
	while ((c = getopt(argc, argv, "")) != -1) {
		switch (c) {
		case '?':
			(void) fprintf(stderr,
			    gettext("invalid option '%c'\n"), optopt);
			usage(B_FALSE);
		}
	}

	if (argc != 2) {
		(void) fprintf(stderr, gettext("wrong number of arguments\n"));
		usage(B_FALSE);
	}

	fsname = argv[1];
	err = zfs_remap_indirects(g_zfs, fsname);

	return (err);
}