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
struct TYPE_3__ {scalar_t__ first; scalar_t__ internal; scalar_t__ longfmt; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ hist_cbdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int for_each_pool (int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  get_history_one ; 
 int getopt (int,char**,char*) ; 
 char* gettext (char*) ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

int
zpool_do_history(int argc, char **argv)
{
	hist_cbdata_t cbdata = { 0 };
	int ret;
	int c;

	cbdata.first = B_TRUE;
	/* check options */
	while ((c = getopt(argc, argv, "li")) != -1) {
		switch (c) {
		case 'l':
			cbdata.longfmt = B_TRUE;
			break;
		case 'i':
			cbdata.internal = B_TRUE;
			break;
		case '?':
			(void) fprintf(stderr, gettext("invalid option '%c'\n"),
			    optopt);
			usage(B_FALSE);
		}
	}
	argc -= optind;
	argv += optind;

	ret = for_each_pool(argc, argv, B_FALSE,  NULL, get_history_one,
	    &cbdata);

	if (argc == 0 && cbdata.first == B_TRUE) {
		(void) printf(gettext("no pools available\n"));
		return (0);
	}

	return (ret);
}