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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 char const* _TEMPFILE ; 
 int /*<<< orphan*/  _TEMPFILEPATH ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int fchmod (int,int) ; 
 char* getenv (char*) ; 
 char* malloc (size_t) ; 
 int mkstemp (char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

void
create_tempfile(char **fn, int *fd)
{
	const char	*tmpdir;
	char		*cp, *tmpf;
	size_t		 tlen, plen;

#define	_TEMPFILE "ecp.XXXXXXXX"
#define	_TEMPFILEPATH "/tmp/ecp.XXXXXXXX"

	if (fn == NULL || fd == NULL)
		return;
	/* Repect TMPDIR environment variable. */
	tmpdir = getenv("TMPDIR");
	if (tmpdir != NULL && *tmpdir != '\0') {
		tlen = strlen(tmpdir);
		plen = strlen(_TEMPFILE);
		tmpf = malloc(tlen + plen + 2);
		if (tmpf == NULL)
			err(EXIT_FAILURE, "malloc failed");
		strncpy(tmpf, tmpdir, tlen);
		cp = &tmpf[tlen - 1];
		if (*cp++ != '/')
			*cp++ = '/';
		strncpy(cp, _TEMPFILE, plen);
		cp[plen] = '\0';
	} else {
		tmpf = strdup(_TEMPFILEPATH);
		if (tmpf == NULL)
			err(EXIT_FAILURE, "strdup failed");
	}
	if ((*fd = mkstemp(tmpf)) == -1)
		err(EXIT_FAILURE, "mkstemp %s failed", tmpf);
	if (fchmod(*fd, 0644) == -1)
		err(EXIT_FAILURE, "fchmod %s failed", tmpf);
	*fn = tmpf;

#undef _TEMPFILE
#undef _TEMPFILEPATH
}