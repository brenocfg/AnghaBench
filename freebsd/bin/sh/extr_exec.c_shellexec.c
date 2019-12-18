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
 int ENOENT ; 
 int ENOEXEC ; 
 int ENOTDIR ; 
 int errno ; 
 int /*<<< orphan*/  errorwithstatus (int,char*,char*,...) ; 
 char* padvance (char const**,char const**,char*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  stunalloc (char*) ; 
 int /*<<< orphan*/  tryexec (char*,char**,char**) ; 

void
shellexec(char **argv, char **envp, const char *path, int idx)
{
	char *cmdname;
	const char *opt;
	int e;

	if (strchr(argv[0], '/') != NULL) {
		tryexec(argv[0], argv, envp);
		e = errno;
	} else {
		e = ENOENT;
		while ((cmdname = padvance(&path, &opt, argv[0])) != NULL) {
			if (--idx < 0 && opt == NULL) {
				tryexec(cmdname, argv, envp);
				if (errno != ENOENT && errno != ENOTDIR)
					e = errno;
				if (e == ENOEXEC)
					break;
			}
			stunalloc(cmdname);
		}
	}

	/* Map to POSIX errors */
	if (e == ENOENT || e == ENOTDIR)
		errorwithstatus(127, "%s: not found", argv[0]);
	else
		errorwithstatus(126, "%s: %s", argv[0], strerror(e));
}