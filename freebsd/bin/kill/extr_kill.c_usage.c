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
 int /*<<< orphan*/  error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{

	(void)fprintf(stderr, "%s\n%s\n%s\n%s\n",
		"usage: kill [-s signal_name] pid ...",
		"       kill -l [exit_status]",
		"       kill -signal_name pid ...",
		"       kill -signal_number pid ...");
#ifdef SHELL
	error(NULL);
#else
	exit(2);
#endif
}