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
typedef  int /*<<< orphan*/  Lst ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIR ; 
 int /*<<< orphan*/  DirExpandCurly (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirExpandInt (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirMatchFiles (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirPrintWord ; 
 int /*<<< orphan*/  Dir_AddDir (int /*<<< orphan*/ ,char*) ; 
 char* Dir_FindFile (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Lst_Destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lst_ForEach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lst_Init (int /*<<< orphan*/ ) ; 
 scalar_t__ UNCONST (char const*) ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  dot ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* strchr (char const*,char) ; 
 int strlen (char*) ; 

void
Dir_Expand(const char *word, Lst path, Lst expansions)
{
    const char    	  *cp;

    if (DEBUG(DIR)) {
	fprintf(debug_file, "Expanding \"%s\"... ", word);
    }

    cp = strchr(word, '{');
    if (cp) {
	DirExpandCurly(word, cp, path, expansions);
    } else {
	cp = strchr(word, '/');
	if (cp) {
	    /*
	     * The thing has a directory component -- find the first wildcard
	     * in the string.
	     */
	    for (cp = word; *cp; cp++) {
		if (*cp == '?' || *cp == '[' || *cp == '*' || *cp == '{') {
		    break;
		}
	    }
	    if (*cp == '{') {
		/*
		 * This one will be fun.
		 */
		DirExpandCurly(word, cp, path, expansions);
		return;
	    } else if (*cp != '\0') {
		/*
		 * Back up to the start of the component
		 */
		char  *dirpath;

		while (cp > word && *cp != '/') {
		    cp--;
		}
		if (cp != word) {
		    char sc;
		    /*
		     * If the glob isn't in the first component, try and find
		     * all the components up to the one with a wildcard.
		     */
		    sc = cp[1];
		    ((char *)UNCONST(cp))[1] = '\0';
		    dirpath = Dir_FindFile(word, path);
		    ((char *)UNCONST(cp))[1] = sc;
		    /*
		     * dirpath is null if can't find the leading component
		     * XXX: Dir_FindFile won't find internal components.
		     * i.e. if the path contains ../Etc/Object and we're
		     * looking for Etc, it won't be found. Ah well.
		     * Probably not important.
		     */
		    if (dirpath != NULL) {
			char *dp = &dirpath[strlen(dirpath) - 1];
			if (*dp == '/')
			    *dp = '\0';
			path = Lst_Init(FALSE);
			(void)Dir_AddDir(path, dirpath);
			DirExpandInt(cp+1, path, expansions);
			Lst_Destroy(path, NULL);
		    }
		} else {
		    /*
		     * Start the search from the local directory
		     */
		    DirExpandInt(word, path, expansions);
		}
	    } else {
		/*
		 * Return the file -- this should never happen.
		 */
		DirExpandInt(word, path, expansions);
	    }
	} else {
	    /*
	     * First the files in dot
	     */
	    DirMatchFiles(word, dot, expansions);

	    /*
	     * Then the files in every other directory on the path.
	     */
	    DirExpandInt(word, path, expansions);
	}
    }
    if (DEBUG(DIR)) {
	Lst_ForEach(expansions, DirPrintWord, NULL);
	fprintf(debug_file, "\n");
    }
}