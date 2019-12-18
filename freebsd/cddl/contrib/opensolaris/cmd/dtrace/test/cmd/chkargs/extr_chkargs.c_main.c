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
typedef  int /*<<< orphan*/  dtrace_probedesc_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_PROBESPEC_NAME ; 
 int /*<<< orphan*/  DTRACE_VERSION ; 
 int /*<<< orphan*/  dtrace_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_ctlfd (int /*<<< orphan*/ *) ; 
 char* dtrace_errmsg (int /*<<< orphan*/ *,int) ; 
 int dtrace_errno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dtrace_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dtrace_probe_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_setopt (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ dtrace_str2desc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int g_count ; 
 int /*<<< orphan*/  g_errexit ; 
 int g_errs ; 
 int /*<<< orphan*/  g_fd ; 
 char* g_progname ; 
 int /*<<< orphan*/  g_verbose ; 
 int getopt (int,char**,char*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 

int
main(int argc, char *argv[])
{
	dtrace_probedesc_t pd, *pdp = NULL;
	dtrace_hdl_t *dtp;
	int err, c;
	char *p;

	g_progname = argv[0];

	if ((dtp = dtrace_open(DTRACE_VERSION, 0, &err)) == NULL) {
		(void) fprintf(stderr, "%s: failed to open dtrace: %s\n",
		    g_progname, dtrace_errmsg(dtp, err));
		return (1);
	}

	while ((c = getopt(argc, argv, "evx:")) != -1) {
		switch (c) {
		case 'e':
			g_errexit++;
			break;
		case 'v':
			g_verbose++;
			break;
		case 'x':
			if ((p = strchr(optarg, '=')) != NULL)
				*p++ = '\0';

			if (dtrace_setopt(dtp, optarg, p) != 0) {
				(void) fprintf(stderr, "%s: failed to set "
				    "option -x %s: %s\n", g_progname, optarg,
				    dtrace_errmsg(dtp, dtrace_errno(dtp)));
				return (2);
			}
			break;

		default:
			(void) fprintf(stderr, "Usage: %s [-ev] "
			    "[-x opt[=arg]] [probedesc]\n", g_progname);
			return (2);
		}
	}

	argv += optind;
	argc -= optind;

	if (argc > 0) {
		if (dtrace_str2desc(dtp, DTRACE_PROBESPEC_NAME, argv[0], &pd)) {
			(void) fprintf(stderr, "%s: invalid probe description "
			    "%s: %s\n", g_progname, argv[0],
			    dtrace_errmsg(dtp, dtrace_errno(dtp)));
			return (2);
		}
		pdp = &pd;
	}

	g_fd = dtrace_ctlfd(dtp);
	(void) dtrace_probe_iter(dtp, pdp, probe, NULL);
	dtrace_close(dtp);

	(void) printf("\nTotal probes: %d\n", g_count);
	(void) printf("Total errors: %d\n\n", g_errs);

	return (g_errs != 0);
}