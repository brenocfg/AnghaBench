#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zpool_list_t ;
struct TYPE_5__ {int cb_iteration; scalar_t__ cb_namewidth; scalar_t__ cb_verbose; int /*<<< orphan*/ * cb_list; } ;
typedef  TYPE_1__ iostat_cbdata_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 scalar_t__ NODATE ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_interval_count (int*,char**,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  get_namewidth ; 
 int /*<<< orphan*/  get_timestamp_arg (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/ * optarg ; 
 scalar_t__ optind ; 
 int optopt ; 
 scalar_t__ pool_list_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pool_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pool_list_get (int,char**,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  pool_list_iter (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pool_list_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_iostat ; 
 int /*<<< orphan*/  print_iostat_header (TYPE_1__*) ; 
 int /*<<< orphan*/  print_iostat_separator (TYPE_1__*) ; 
 int /*<<< orphan*/  print_timestamp (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  refresh_iostat ; 
 int /*<<< orphan*/  sleep (unsigned long) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ timestamp_fmt ; 
 int /*<<< orphan*/  usage (scalar_t__) ; 

int
zpool_do_iostat(int argc, char **argv)
{
	int c;
	int ret;
	int npools;
	unsigned long interval = 0, count = 0;
	zpool_list_t *list;
	boolean_t verbose = B_FALSE;
	iostat_cbdata_t cb;

	/* check options */
	while ((c = getopt(argc, argv, "T:v")) != -1) {
		switch (c) {
		case 'T':
			get_timestamp_arg(*optarg);
			break;
		case 'v':
			verbose = B_TRUE;
			break;
		case '?':
			(void) fprintf(stderr, gettext("invalid option '%c'\n"),
			    optopt);
			usage(B_FALSE);
		}
	}

	argc -= optind;
	argv += optind;

	get_interval_count(&argc, argv, &interval, &count);

	/*
	 * Construct the list of all interesting pools.
	 */
	ret = 0;
	if ((list = pool_list_get(argc, argv, NULL, &ret)) == NULL)
		return (1);

	if (pool_list_count(list) == 0 && argc != 0) {
		pool_list_free(list);
		return (1);
	}

	if (pool_list_count(list) == 0 && interval == 0) {
		pool_list_free(list);
		(void) fprintf(stderr, gettext("no pools available\n"));
		return (1);
	}

	/*
	 * Enter the main iostat loop.
	 */
	cb.cb_list = list;
	cb.cb_verbose = verbose;
	cb.cb_iteration = 0;
	cb.cb_namewidth = 0;

	for (;;) {
		pool_list_update(list);

		if ((npools = pool_list_count(list)) == 0)
			break;

		/*
		 * Refresh all statistics.  This is done as an explicit step
		 * before calculating the maximum name width, so that any
		 * configuration changes are properly accounted for.
		 */
		(void) pool_list_iter(list, B_FALSE, refresh_iostat, &cb);

		/*
		 * Iterate over all pools to determine the maximum width
		 * for the pool / device name column across all pools.
		 */
		cb.cb_namewidth = 0;
		(void) pool_list_iter(list, B_FALSE, get_namewidth, &cb);

		if (timestamp_fmt != NODATE)
			print_timestamp(timestamp_fmt);

		/*
		 * If it's the first time, or verbose mode, print the header.
		 */
		if (++cb.cb_iteration == 1 || verbose)
			print_iostat_header(&cb);

		(void) pool_list_iter(list, B_FALSE, print_iostat, &cb);

		/*
		 * If there's more than one pool, and we're not in verbose mode
		 * (which prints a separator for us), then print a separator.
		 */
		if (npools > 1 && !verbose)
			print_iostat_separator(&cb);

		if (verbose)
			(void) printf("\n");

		/*
		 * Flush the output so that redirection to a file isn't buffered
		 * indefinitely.
		 */
		(void) fflush(stdout);

		if (interval == 0)
			break;

		if (count != 0 && --count == 0)
			break;

		(void) sleep(interval);
	}

	pool_list_free(list);

	return (ret);
}