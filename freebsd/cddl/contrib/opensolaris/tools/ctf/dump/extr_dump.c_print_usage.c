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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int E_USAGE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* getpname () ; 

__attribute__((used)) static int
print_usage(FILE *fp, int verbose)
{
	(void) fprintf(fp, "Usage: %s [-dfhlsSt] [-u file] file\n", getpname());

	if (verbose) {
		(void) fprintf(fp,
		    "\t-d  dump data object section\n"
		    "\t-f  dump function section\n"
		    "\t-h  dump file header\n"
		    "\t-l  dump label table\n"
		    "\t-s  dump string table\n"
		    "\t-S  dump statistics\n"
		    "\t-t  dump type section\n"
		    "\t-u  save uncompressed CTF to a file\n");
	}

	return (E_USAGE);
}