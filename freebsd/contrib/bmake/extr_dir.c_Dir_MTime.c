#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_mtime; } ;
struct TYPE_6__ {int type; int mtime; char* path; char* name; int flags; char* fname; int lineno; int /*<<< orphan*/  iParents; } ;
typedef  TYPE_1__ GNode ;
typedef  scalar_t__ Boolean ;

/* Variables and functions */
 int Arch_MTime (TYPE_1__*) ; 
 int Arch_MemMTime (TYPE_1__*) ; 
 int /*<<< orphan*/  CST_UPDATE ; 
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIR ; 
 char* Dir_FindFile (char*,int /*<<< orphan*/ ) ; 
 int FROM_DEPEND ; 
 int /*<<< orphan*/  Job_RunTarget (char*,char*) ; 
 int /*<<< orphan*/  Lst_IsEmpty (int /*<<< orphan*/ ) ; 
 int OP_ARCHV ; 
 int OP_MEMBER ; 
 int OP_NOPATH ; 
 int OP_PHONY ; 
 int /*<<< orphan*/  Suff_FindPath (TYPE_1__*) ; 
 void* bmake_strdup (char*) ; 
 scalar_t__ cached_stats (int /*<<< orphan*/ *,char*,struct stat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* makeDependfile ; 
 int /*<<< orphan*/  mtimes ; 
 char* progname ; 
 int /*<<< orphan*/  stdout ; 
 char* strrchr (char*,char) ; 

int
Dir_MTime(GNode *gn, Boolean recheck)
{
    char          *fullName;  /* the full pathname of name */
    struct stat	  stb;	      /* buffer for finding the mod time */

    if (gn->type & OP_ARCHV) {
	return Arch_MTime(gn);
    } else if (gn->type & OP_PHONY) {
	gn->mtime = 0;
	return 0;
    } else if (gn->path == NULL) {
	if (gn->type & OP_NOPATH)
	    fullName = NULL;
	else {
	    fullName = Dir_FindFile(gn->name, Suff_FindPath(gn));
	    if (fullName == NULL && gn->flags & FROM_DEPEND &&
		!Lst_IsEmpty(gn->iParents)) {
		char *cp;

		cp = strrchr(gn->name, '/');
		if (cp) {
		    /*
		     * This is an implied source, and it may have moved,
		     * see if we can find it via the current .PATH
		     */
		    cp++;
			
		    fullName = Dir_FindFile(cp, Suff_FindPath(gn));
		    if (fullName) {
			/*
			 * Put the found file in gn->path
			 * so that we give that to the compiler.
			 */
			gn->path = bmake_strdup(fullName);
			if (!Job_RunTarget(".STALE", gn->fname))
			    fprintf(stdout,
				"%s: %s, %d: ignoring stale %s for %s, "
				"found %s\n", progname, gn->fname, gn->lineno,
				makeDependfile, gn->name, fullName);
		    }
		}
	    }
	    if (DEBUG(DIR))
		fprintf(debug_file, "Found '%s' as '%s'\n",
			gn->name, fullName ? fullName : "(not found)" );
	}
    } else {
	fullName = gn->path;
    }

    if (fullName == NULL) {
	fullName = bmake_strdup(gn->name);
    }

    if (cached_stats(&mtimes, fullName, &stb, recheck ? CST_UPDATE : 0) < 0) {
	if (gn->type & OP_MEMBER) {
	    if (fullName != gn->path)
		free(fullName);
	    return Arch_MemMTime(gn);
	} else {
	    stb.st_mtime = 0;
	}
    }

    if (fullName && gn->path == NULL) {
	gn->path = fullName;
    }

    gn->mtime = stb.st_mtime;
    return (gn->mtime);
}