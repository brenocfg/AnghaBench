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
typedef  int /*<<< orphan*/  _TFILE_BASE ;

/* Variables and functions */
#define  APPND 132 
#define  ARCHIVE 131 
#define  COPY 130 
#define  EXTRACT 129 
 int /*<<< orphan*/  LC_ALL ; 
#define  LIST 128 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 char* _PATH_TMP ; 
 int act ; 
 int /*<<< orphan*/  append () ; 
 int /*<<< orphan*/  archive () ; 
 int /*<<< orphan*/  copy () ; 
 scalar_t__ cwdfd ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errno ; 
 int exit_val ; 
 int /*<<< orphan*/  extract () ; 
 scalar_t__ gen_init () ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/ * gzip_program ; 
 int /*<<< orphan*/  list () ; 
 int /*<<< orphan*/  listf ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,size_t) ; 
 scalar_t__ open (char*,int) ; 
 int /*<<< orphan*/  options (int,char**) ; 
 int /*<<< orphan*/  paxwarn (int,char*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  syswarn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * tempbase ; 
 int /*<<< orphan*/ * tempfile ; 
 scalar_t__ tty_init () ; 

int
main(int argc, char *argv[])
{
	const char *tmpdir;
	size_t tdlen;

	(void) setlocale(LC_ALL, "");
	listf = stderr;
	/*
	 * Keep a reference to cwd, so we can always come back home.
	 */
	cwdfd = open(".", O_RDONLY | O_CLOEXEC);
	if (cwdfd < 0) {
		syswarn(0, errno, "Can't open current working directory.");
		return(exit_val);
	}

	/*
	 * Where should we put temporary files?
	 */
	if ((tmpdir = getenv("TMPDIR")) == NULL || *tmpdir == '\0')
		tmpdir = _PATH_TMP;
	tdlen = strlen(tmpdir);
	while (tdlen > 0 && tmpdir[tdlen - 1] == '/')
		tdlen--;
	tempfile = malloc(tdlen + 1 + sizeof(_TFILE_BASE));
	if (tempfile == NULL) {
		paxwarn(1, "Cannot allocate memory for temp file name.");
		return(exit_val);
	}
	if (tdlen)
		memcpy(tempfile, tmpdir, tdlen);
	tempbase = tempfile + tdlen;
	*tempbase++ = '/';

	/*
	 * parse options, determine operational mode, general init
	 */
	options(argc, argv);
	if ((gen_init() < 0) || (tty_init() < 0))
		return(exit_val);

	/*
	 * select a primary operation mode
	 */
	switch (act) {
	case EXTRACT:
		extract();
		break;
	case ARCHIVE:
		archive();
		break;
	case APPND:
		if (gzip_program != NULL)
			err(1, "can not gzip while appending");
		append();
		break;
	case COPY:
		copy();
		break;
	default:
	case LIST:
		list();
		break;
	}
	return(exit_val);
}