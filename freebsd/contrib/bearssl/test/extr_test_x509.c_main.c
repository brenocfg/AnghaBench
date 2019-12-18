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
 int /*<<< orphan*/  CONFFILE ; 
 int /*<<< orphan*/  HT_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _chdir (char*) ; 
 char* all_chains ; 
 size_t all_chains_ptr ; 
 int chdir (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free_key ; 
 int /*<<< orphan*/  free_test_case_contents (char*) ; 
 int /*<<< orphan*/  free_trust_anchor ; 
 int /*<<< orphan*/  keys ; 
 scalar_t__ max_dp_usage ; 
 scalar_t__ max_rp_usage ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 
 int /*<<< orphan*/  process_conf_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_test_case (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  test_name_extraction () ; 
 int /*<<< orphan*/  trust_anchors ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xmalloc (size_t) ; 

int
main(int argc, const char *argv[])
{
	size_t u;

#ifdef SRCDIRNAME
	/*
	 * We want to change the current directory to that of the
	 * executable, so that test files are reliably located. We
	 * do that only if SRCDIRNAME is defined (old Makefile would
	 * not do that).
	 */
	if (argc >= 1) {
		const char *arg, *c;

		arg = argv[0];
		for (c = arg + strlen(arg);; c --) {
			int sep, r;

#ifdef _WIN32
			sep = (*c == '/') || (*c == '\\');
#else
			sep = (*c == '/');
#endif
			if (sep) {
				size_t len;
				char *dn;

				len = 1 + (c - arg);
				dn = xmalloc(len + 1);
				memcpy(dn, arg, len);
				dn[len] = 0;
#ifdef _WIN32
				r = _chdir(dn);
#else
				r = chdir(dn);
#endif
				if (r != 0) {
					fprintf(stderr, "warning: could not"
						" set directory to '%s'\n", dn);
				}
				xfree(dn);
				break;
			}
			if (c == arg) {
				break;
			}
		}
	}
#else
	(void)argc;
	(void)argv;
#endif

	process_conf_file(CONFFILE);

	max_dp_usage = 0;
	max_rp_usage = 0;
	for (u = 0; u < all_chains_ptr; u ++) {
		run_test_case(&all_chains[u]);
	}
	test_name_extraction();

	printf("Maximum data stack usage:    %u\n", (unsigned)max_dp_usage);
	printf("Maximum return stack usage:  %u\n", (unsigned)max_rp_usage);

	HT_free(keys, free_key);
	HT_free(trust_anchors, free_trust_anchor);
	for (u = 0; u < all_chains_ptr; u ++) {
		free_test_case_contents(&all_chains[u]);
	}
	xfree(all_chains);

	return 0;
}