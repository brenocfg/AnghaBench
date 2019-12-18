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
typedef  int /*<<< orphan*/  WSADATA ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ do_chain (int,char**) ; 
 scalar_t__ do_client (int,char**) ; 
 scalar_t__ do_impl (int,char**) ; 
 scalar_t__ do_server (int,char**) ; 
 scalar_t__ do_skey (int,char**) ; 
 scalar_t__ do_ta (int,char**) ; 
 int do_twrch (int,char**) ; 
 scalar_t__ do_verify (int,char**) ; 
 scalar_t__ eqstr (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	char *cmd;

	if (argc < 2) {
		usage();
		return EXIT_FAILURE;
	}
#ifdef _WIN32
	{
		WSADATA wd;
		int r;

		r = WSAStartup(MAKEWORD(2, 2), &wd);
		if (r != 0) {
			fprintf(stderr, "WARNING: network initialisation"
				" failed (WSAStartup() returned %d)\n", r);
		}
	}
#endif
	cmd = argv[1];
	if (eqstr(cmd, "client")) {
		if (do_client(argc - 2, argv + 2) < 0) {
			return EXIT_FAILURE;
		}
	} else if (eqstr(cmd, "server")) {
		if (do_server(argc - 2, argv + 2) < 0) {
			return EXIT_FAILURE;
		}
	} else if (eqstr(cmd, "verify")) {
		if (do_verify(argc - 2, argv + 2) < 0) {
			return EXIT_FAILURE;
		}
	} else if (eqstr(cmd, "skey")) {
		if (do_skey(argc - 2, argv + 2) < 0) {
			return EXIT_FAILURE;
		}
	} else if (eqstr(cmd, "ta")) {
		if (do_ta(argc - 2, argv + 2) < 0) {
			return EXIT_FAILURE;
		}
	} else if (eqstr(cmd, "chain")) {
		if (do_chain(argc - 2, argv + 2) < 0) {
			return EXIT_FAILURE;
		}
	} else if (eqstr(cmd, "twrch")) {
		int ret;

		ret = do_twrch(argc - 2, argv + 2);
		if (ret < 0) {
			return EXIT_FAILURE;
		} else {
			return ret;
		}
	} else if (eqstr(cmd, "impl")) {
		if (do_impl(argc - 2, argv + 2) < 0) {
			return EXIT_FAILURE;
		}
	} else {
		fprintf(stderr, "unknown command: '%s'\n", cmd);
		usage();
		return EXIT_FAILURE;
	}
	return 0;
}