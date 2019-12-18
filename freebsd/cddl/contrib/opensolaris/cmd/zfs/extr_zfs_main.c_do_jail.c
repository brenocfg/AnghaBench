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
typedef  int /*<<< orphan*/  zfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_zfs ; 
 char* gettext (char*) ; 
 int jail_getid (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_jail (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
do_jail(int argc, char **argv, int attach)
{
	zfs_handle_t *zhp;
	int jailid, ret;

	/* check number of arguments */
	if (argc < 3) {
		(void) fprintf(stderr, gettext("missing argument(s)\n"));
		usage(B_FALSE);
	}
	if (argc > 3) {
		(void) fprintf(stderr, gettext("too many arguments\n"));
		usage(B_FALSE);
	}

	jailid = jail_getid(argv[1]);
	if (jailid < 0) {
		(void) fprintf(stderr, gettext("invalid jail id or name\n"));
		usage(B_FALSE);
	}

	zhp = zfs_open(g_zfs, argv[2], ZFS_TYPE_FILESYSTEM);
	if (zhp == NULL)
		return (1);

	ret = (zfs_jail(zhp, jailid, attach) != 0);

	zfs_close(zhp);
	return (ret);
}