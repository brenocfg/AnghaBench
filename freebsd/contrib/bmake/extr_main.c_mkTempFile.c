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
typedef  int /*<<< orphan*/  tfile ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  Punt (char*,char*,int /*<<< orphan*/ ) ; 
 char* TMPPAT ; 
 char* bmake_strdup (char*) ; 
 int /*<<< orphan*/  errno ; 
 char* getTmpdir () ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 

int
mkTempFile(const char *pattern, char **fnamep)
{
    static char *tmpdir = NULL;
    char tfile[MAXPATHLEN];
    int fd;
    
    if (!pattern)
	pattern = TMPPAT;
    if (!tmpdir)
	tmpdir = getTmpdir();
    if (pattern[0] == '/') {
	snprintf(tfile, sizeof(tfile), "%s", pattern);
    } else {
	snprintf(tfile, sizeof(tfile), "%s%s", tmpdir, pattern);
    }
    if ((fd = mkstemp(tfile)) < 0)
	Punt("Could not create temporary file %s: %s", tfile, strerror(errno));
    if (fnamep) {
	*fnamep = bmake_strdup(tfile);
    } else {
	unlink(tfile);			/* we just want the descriptor */
    }
    return fd;
}