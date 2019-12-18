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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(char *pnam)
{
	(void) fprintf(stderr, "Usage:\n    %s -l [-is] dir-to-look-in "
	    "file-in-dir [xfile-on-file]\n", pnam);
	(void) fprintf(stderr, "    %s -i [-ls] dir-to-look-in "
	    "file-in-dir [xfile-on-file]\n", pnam);
	(void) fprintf(stderr, "    %s -s [-il] dir-to-look-in "
	    "file-in-dir [xfile-on-file]\n", pnam);
	(void) fprintf(stderr, "\t    Perform a lookup\n");
	(void) fprintf(stderr, "\t    -l == lookup\n");
	(void) fprintf(stderr, "\t    -i == request FIGNORECASE\n");
	(void) fprintf(stderr, "\t    -s == request stat(2) and xvattr info\n");
	(void) fprintf(stderr, "    %s -r [-ea] [-b buffer-size-in-bytes] "
	    "dir-to-look-in [file-in-dir]\n", pnam);
	(void) fprintf(stderr, "    %s -e [-ra] [-b buffer-size-in-bytes] "
	    "dir-to-look-in [file-in-dir]\n", pnam);
	(void) fprintf(stderr, "    %s -a [-re] [-b buffer-size-in-bytes] "
	    "dir-to-look-in [file-in-dir]\n", pnam);
	(void) fprintf(stderr, "\t    Perform a readdir\n");
	(void) fprintf(stderr, "\t    -r == readdir\n");
	(void) fprintf(stderr, "\t    -e == request extended entries\n");
	(void) fprintf(stderr, "\t    -a == request access filtering\n");
	(void) fprintf(stderr, "\t    -b == buffer size (default 4K)\n");
	(void) fprintf(stderr, "    %s -A path\n", pnam);
	(void) fprintf(stderr, "\t    Look up _PC_ACCESS_FILTERING "
	    "for path with pathconf(2)\n");
	(void) fprintf(stderr, "    %s -E path\n", pnam);
	(void) fprintf(stderr, "\t    Look up _PC_SATTR_EXISTS "
	    "for path with pathconf(2)\n");
	(void) fprintf(stderr, "    %s -S path\n", pnam);
	(void) fprintf(stderr, "\t    Look up _PC_SATTR_EXISTS "
	    "for path with pathconf(2)\n");
	exit(EINVAL);
}