#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct loadedfile {int dummy; } ;
struct TYPE_2__ {char* fname; struct loadedfile* lf; } ;
typedef  int /*<<< orphan*/ * Lst ;
typedef  scalar_t__ Boolean ;

/* Variables and functions */
 char* Dir_FindFile (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ Lst_IsEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PARSE_FATAL ; 
 int /*<<< orphan*/  ParseSetIncludedFile () ; 
 int /*<<< orphan*/  Parse_Error (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  Parse_SetInput (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct loadedfile*) ; 
 int /*<<< orphan*/  STR_ADDSLASH ; 
 int /*<<< orphan*/ * Suff_GetPath (char*) ; 
 char* bmake_strdup (char*) ; 
 TYPE_1__* curFile ; 
 int /*<<< orphan*/ * defIncPath ; 
 int /*<<< orphan*/ * dirSearchPath ; 
 scalar_t__ doing_depend ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  loadedfile_nextbuf ; 
 struct loadedfile* loadfile (char*,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * parseIncPath ; 
 char* str_concat (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/ * sysIncPath ; 

__attribute__((used)) static void
Parse_include_file(char *file, Boolean isSystem, Boolean depinc, int silent)
{
    struct loadedfile *lf;
    char          *fullname;	/* full pathname of file */
    char          *newName;
    char          *prefEnd, *incdir;
    int           fd;
    int           i;

    /*
     * Now we know the file's name and its search path, we attempt to
     * find the durn thing. A return of NULL indicates the file don't
     * exist.
     */
    fullname = file[0] == '/' ? bmake_strdup(file) : NULL;

    if (fullname == NULL && !isSystem) {
	/*
	 * Include files contained in double-quotes are first searched for
	 * relative to the including file's location. We don't want to
	 * cd there, of course, so we just tack on the old file's
	 * leading path components and call Dir_FindFile to see if
	 * we can locate the beast.
	 */

	incdir = bmake_strdup(curFile->fname);
	prefEnd = strrchr(incdir, '/');
	if (prefEnd != NULL) {
	    *prefEnd = '\0';
	    /* Now do lexical processing of leading "../" on the filename */
	    for (i = 0; strncmp(file + i, "../", 3) == 0; i += 3) {
		prefEnd = strrchr(incdir + 1, '/');
		if (prefEnd == NULL || strcmp(prefEnd, "/..") == 0)
		    break;
		*prefEnd = '\0';
	    }
	    newName = str_concat(incdir, file + i, STR_ADDSLASH);
	    fullname = Dir_FindFile(newName, parseIncPath);
	    if (fullname == NULL)
		fullname = Dir_FindFile(newName, dirSearchPath);
	    free(newName);
	}
	free(incdir);

	if (fullname == NULL) {
	    /*
    	     * Makefile wasn't found in same directory as included makefile.
	     * Search for it first on the -I search path,
	     * then on the .PATH search path, if not found in a -I directory.
	     * If we have a suffix specific path we should use that.
	     */
	    char *suff;
	    Lst	suffPath = NULL;

	    if ((suff = strrchr(file, '.'))) {
		suffPath = Suff_GetPath(suff);
		if (suffPath != NULL) {
		    fullname = Dir_FindFile(file, suffPath);
		}
	    }
	    if (fullname == NULL) {
		fullname = Dir_FindFile(file, parseIncPath);
		if (fullname == NULL) {
		    fullname = Dir_FindFile(file, dirSearchPath);
		}
	    }
	}
    }

    /* Looking for a system file or file still not found */
    if (fullname == NULL) {
	/*
	 * Look for it on the system path
	 */
	fullname = Dir_FindFile(file,
		    Lst_IsEmpty(sysIncPath) ? defIncPath : sysIncPath);
    }

    if (fullname == NULL) {
	if (!silent)
	    Parse_Error(PARSE_FATAL, "Could not find %s", file);
	return;
    }

    /* Actually open the file... */
    fd = open(fullname, O_RDONLY);
    if (fd == -1) {
	if (!silent)
	    Parse_Error(PARSE_FATAL, "Cannot open %s", fullname);
	free(fullname);
	return;
    }

    /* load it */
    lf = loadfile(fullname, fd);

    ParseSetIncludedFile();
    /* Start reading from this file next */
    Parse_SetInput(fullname, 0, -1, loadedfile_nextbuf, lf);
    curFile->lf = lf;
    if (depinc)
	doing_depend = depinc;		/* only turn it on */
}