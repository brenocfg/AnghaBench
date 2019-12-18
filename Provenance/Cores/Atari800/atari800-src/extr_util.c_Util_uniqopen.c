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
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  Util_fileexists (char*) ; 
 int /*<<< orphan*/ * fdopen (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * fopen (char*,char const*) ; 
 int /*<<< orphan*/  mkstemp (char*) ; 
 char* mktemp (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* tmpnam (char*) ; 

FILE *Util_uniqopen(char *filename, const char *mode)
{
	/* We cannot simply call tmpfile(), because we don't want the file
	   to be deleted when we close it, and we need the filename. */

#if defined(HAVE_MKSTEMP) && defined(HAVE_FDOPEN)
	/* this is the only implementation without a race condition */
	strcpy(filename, "a8XXXXXX");
	/* mkstemp() modifies the 'X'es and returns an open descriptor */
	return fdopen(mkstemp(filename), mode);
#elif defined(HAVE_TMPNAM)
	/* tmpnam() is better than mktemp(), because it creates filenames
	   in system's temporary directory. It is also more portable. */
	return fopen(tmpnam(filename), mode);
#elif defined(HAVE_MKTEMP)
	strcpy(filename, "a8XXXXXX");
	/* mktemp() modifies the 'X'es and returns filename */
	return fopen(mktemp(filename), mode);
#else
	/* Roll-your-own */
	int no;
	for (no = 0; no < 1000000; no++) {
		snprintf(filename, FILENAME_MAX, "a8%06d", no);
		if (!Util_fileexists(filename))
			return fopen(filename, mode);
	}
	return NULL;
#endif
}