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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	(void)fprintf(stderr, "%s\n%s\n%s\n",
	    "usage: ln [-s [-F] | -L | -P] [-f | -i] [-hnv] source_file [target_file]",
	    "       ln [-s [-F] | -L | -P] [-f | -i] [-hnv] source_file ... target_dir",
	    "       link source_file target_file");
	exit(1);
}