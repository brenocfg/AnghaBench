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
struct TYPE_3__ {scalar_t__ cb_count; void* cb_allpools; void* cb_first; void* cb_explain; void* cb_dedup_stats; void* cb_verbose; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ status_cbdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 void* B_TRUE ; 
 scalar_t__ NODATE ; 
 int for_each_pool (int,char**,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  get_interval_count (int*,char**,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  get_timestamp_arg (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/ * optarg ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  print_timestamp (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sleep (unsigned long) ; 
 int /*<<< orphan*/  status_callback ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ timestamp_fmt ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

int
zpool_do_status(int argc, char **argv)
{
	int c;
	int ret;
	unsigned long interval = 0, count = 0;
	status_cbdata_t cb = { 0 };

	/* check options */
	while ((c = getopt(argc, argv, "vxDT:")) != -1) {
		switch (c) {
		case 'v':
			cb.cb_verbose = B_TRUE;
			break;
		case 'x':
			cb.cb_explain = B_TRUE;
			break;
		case 'D':
			cb.cb_dedup_stats = B_TRUE;
			break;
		case 'T':
			get_timestamp_arg(*optarg);
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

	if (argc == 0)
		cb.cb_allpools = B_TRUE;

	cb.cb_first = B_TRUE;

	for (;;) {
		if (timestamp_fmt != NODATE)
			print_timestamp(timestamp_fmt);

		ret = for_each_pool(argc, argv, B_TRUE, NULL,
		    status_callback, &cb);

		if (argc == 0 && cb.cb_count == 0)
			(void) printf(gettext("no pools available\n"));
		else if (cb.cb_explain && cb.cb_first && cb.cb_allpools)
			(void) printf(gettext("all pools are healthy\n"));

		if (ret != 0)
			return (ret);

		if (interval == 0)
			break;

		if (count != 0 && --count == 0)
			break;

		(void) sleep(interval);
	}

	return (0);
}