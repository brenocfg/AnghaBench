#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct TYPE_3__ {void* recurse; void* nounmount; void* forceunmount; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ renameflags_t ;
typedef  void* boolean_t ;

/* Variables and functions */
 void* B_FALSE ; 
 void* B_TRUE ; 
 int ZFS_TYPE_BOOKMARK ; 
 int ZFS_TYPE_DATASET ; 
 int ZFS_TYPE_FILESYSTEM ; 
 int ZFS_TYPE_VOLUME ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_zfs ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  usage (void*) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_create_ancestors (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_get_type (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_name_valid (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ zfs_rename (int /*<<< orphan*/ *,char*,char*,TYPE_1__) ; 

__attribute__((used)) static int
zfs_do_rename(int argc, char **argv)
{
	zfs_handle_t *zhp;
	renameflags_t flags = { 0 };
	int c;
	int ret = 0;
	int types;
	boolean_t parents = B_FALSE;
	boolean_t bookmarks = B_FALSE;
	char *snapshot = NULL;

	/* check options */
	while ((c = getopt(argc, argv, "fpru")) != -1) {
		switch (c) {
		case 'p':
			parents = B_TRUE;
			break;
		case 'r':
			flags.recurse = B_TRUE;
			break;
		case 'u':
			flags.nounmount = B_TRUE;
			break;
		case 'f':
			flags.forceunmount = B_TRUE;
			break;
		case '?':
		default:
			(void) fprintf(stderr, gettext("invalid option '%c'\n"),
			    optopt);
			usage(B_FALSE);
		}
	}

	argc -= optind;
	argv += optind;

	/* check number of arguments */
	if (argc < 1) {
		(void) fprintf(stderr, gettext("missing source dataset "
		    "argument\n"));
		usage(B_FALSE);
	}
	if (argc < 2) {
		(void) fprintf(stderr, gettext("missing target dataset "
		    "argument\n"));
		usage(B_FALSE);
	}
	if (argc > 2) {
		(void) fprintf(stderr, gettext("too many arguments\n"));
		usage(B_FALSE);
	}

	if (flags.recurse && parents) {
		(void) fprintf(stderr, gettext("-p and -r options are mutually "
		    "exclusive\n"));
		usage(B_FALSE);
	}

	if (flags.recurse && strchr(argv[0], '@') == NULL) {
		(void) fprintf(stderr, gettext("source dataset for recursive "
		    "rename must be a snapshot\n"));
		usage(B_FALSE);
	}

	if (flags.nounmount && parents) {
		(void) fprintf(stderr, gettext("-u and -p options are mutually "
		    "exclusive\n"));
		usage(B_FALSE);
	}

	if (strchr(argv[0], '#') != NULL)
		bookmarks = B_TRUE;

	if (bookmarks && (flags.nounmount || flags.recurse ||
	    flags.forceunmount || parents)) {
		(void) fprintf(stderr, gettext("options are not supported "
		    "for renaming bookmarks\n"));
		usage(B_FALSE);
	}

	if (flags.nounmount)
		types = ZFS_TYPE_FILESYSTEM;
	else if (parents)
		types = ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME;
	else if (bookmarks)
		types = ZFS_TYPE_BOOKMARK;
	else
		types = ZFS_TYPE_DATASET;

	if (flags.recurse) {
		/*
		 * When we do recursive rename we are fine when the given
		 * snapshot for the given dataset doesn't exist - it can
		 * still exists below.
		 */

		snapshot = strchr(argv[0], '@');
		assert(snapshot != NULL);
		*snapshot = '\0';
		snapshot++;
	}

	if ((zhp = zfs_open(g_zfs, argv[0], types)) == NULL)
		return (1);

	/* If we were asked and the name looks good, try to create ancestors. */
	if (parents && zfs_name_valid(argv[1], zfs_get_type(zhp)) &&
	    zfs_create_ancestors(g_zfs, argv[1]) != 0) {
		zfs_close(zhp);
		return (1);
	}

	ret = (zfs_rename(zhp, snapshot, argv[1], flags) != 0);

	zfs_close(zhp);
	return (ret);
}