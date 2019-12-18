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
 int /*<<< orphan*/  NM_CPIO ; 
 char* NM_PAX ; 
 int /*<<< orphan*/  NM_TAR ; 
 char* argv0 ; 
 int /*<<< orphan*/  cpio_options (int,char**) ; 
 int /*<<< orphan*/  pax_options (int,char**) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  tar_options (int,char**) ; 

void
options(int argc, char **argv)
{

	/*
	 * Are we acting like pax, tar or cpio (based on argv[0])
	 */
	if ((argv0 = strrchr(argv[0], '/')) != NULL)
		argv0++;
	else
		argv0 = argv[0];

	if (strcmp(NM_TAR, argv0) == 0) {
		tar_options(argc, argv);
		return;
	}
	else if (strcmp(NM_CPIO, argv0) == 0) {
		cpio_options(argc, argv);
		return;
	}
	/*
	 * assume pax as the default
	 */
	argv0 = NM_PAX;
	pax_options(argc, argv);
	return;
}