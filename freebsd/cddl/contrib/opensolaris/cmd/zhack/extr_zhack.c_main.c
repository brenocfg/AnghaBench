#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char** path; int paths; void* cachefile; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  FTAG ; 
 int MAX_NUM_PATHS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dprintf_setup (int*,char**) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__ g_importargs ; 
 int /*<<< orphan*/  g_pool ; 
 int /*<<< orphan*/  g_readonly ; 
 int /*<<< orphan*/  g_zfs ; 
 char getopt (int,char**,char*) ; 
 int /*<<< orphan*/  kernel_fini () ; 
 int /*<<< orphan*/  libzfs_fini (int /*<<< orphan*/ ) ; 
 void* optarg ; 
 int optind ; 
 scalar_t__ spa_export (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int zhack_do_feature (int,char**) ; 

int
main(int argc, char **argv)
{
	extern void zfs_prop_init(void);

	char *path[MAX_NUM_PATHS];
	const char *subcommand;
	int rv = 0;
	char c;

	g_importargs.path = path;

	dprintf_setup(&argc, argv);
	zfs_prop_init();

	while ((c = getopt(argc, argv, "c:d:")) != -1) {
		switch (c) {
		case 'c':
			g_importargs.cachefile = optarg;
			break;
		case 'd':
			assert(g_importargs.paths < MAX_NUM_PATHS);
			g_importargs.path[g_importargs.paths++] = optarg;
			break;
		default:
			usage();
			break;
		}
	}

	argc -= optind;
	argv += optind;
	optind = 1;

	if (argc == 0) {
		(void) fprintf(stderr, "error: no command specified\n");
		usage();
	}

	subcommand = argv[0];

	if (strcmp(subcommand, "feature") == 0) {
		rv = zhack_do_feature(argc, argv);
	} else {
		(void) fprintf(stderr, "error: unknown subcommand: %s\n",
		    subcommand);
		usage();
	}

	if (!g_readonly && spa_export(g_pool, NULL, B_TRUE, B_FALSE) != 0) {
		fatal(NULL, FTAG, "pool export failed; "
		    "changes may not be committed to disk\n");
	}

	libzfs_fini(g_zfs);
	kernel_fini();

	return (rv);
}