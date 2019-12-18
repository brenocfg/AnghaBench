#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  files; } ;
typedef  TYPE_1__ Path ;
typedef  int /*<<< orphan*/ * LstNode ;
typedef  int /*<<< orphan*/  Lst ;
typedef  scalar_t__ Boolean ;

/* Variables and functions */
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIR ; 
 char* DirFindDot (scalar_t__,char const*,char const*) ; 
 char* DirLookup (TYPE_1__*,char const*,char const*,scalar_t__) ; 
 char* DirLookupAbs (TYPE_1__*,char const*,char const*) ; 
 char* DirLookupSubdir (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  Dir_AddDir (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ FAILURE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/ * Hash_FindEntry (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  Lst_Close (int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_Datum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Lst_First (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Lst_Last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Lst_Next (int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_Open (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int bigmisses ; 
 char* bmake_strdup (char const*) ; 
 scalar_t__ cached_stat (char const*,struct stat*) ; 
 TYPE_1__* cur ; 
 int /*<<< orphan*/  debug_file ; 
 TYPE_1__* dot ; 
 TYPE_1__* dotLast ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int misses ; 
 char* strrchr (char const*,char) ; 
 char const* traling_dot ; 

char *
Dir_FindFile(const char *name, Lst path)
{
    LstNode       ln;			/* a list element */
    char	  *file;		/* the current filename to check */
    Path	  *p;			/* current path member */
    const char	  *cp;			/* Terminal name of file */
    Boolean	  hasLastDot = FALSE;	/* true we should search dot last */
    Boolean	  hasSlash;		/* true if 'name' contains a / */
    struct stat	  stb;			/* Buffer for stat, if necessary */
    const char   *trailing_dot = ".";

    /*
     * Find the final component of the name and note whether it has a
     * slash in it (the name, I mean)
     */
    cp = strrchr(name, '/');
    if (cp) {
	hasSlash = TRUE;
	cp += 1;
    } else {
	hasSlash = FALSE;
	cp = name;
    }

    if (DEBUG(DIR)) {
	fprintf(debug_file, "Searching for %s ...", name);
    }

    if (Lst_Open(path) == FAILURE) {
	if (DEBUG(DIR)) {
	    fprintf(debug_file, "couldn't open path, file not found\n");
	}
	misses += 1;
	return NULL;
    }

    if ((ln = Lst_First(path)) != NULL) {
	p = (Path *)Lst_Datum(ln);
	if (p == dotLast) {
	    hasLastDot = TRUE;
            if (DEBUG(DIR))
		fprintf(debug_file, "[dot last]...");
	}
    }
    if (DEBUG(DIR)) {
	fprintf(debug_file, "\n");
    }

    /*
     * If there's no leading directory components or if the leading
     * directory component is exactly `./', consult the cached contents
     * of each of the directories on the search path.
     */
    if (!hasSlash || (cp - name == 2 && *name == '.')) {
	    /*
	     * We look through all the directories on the path seeking one which
	     * contains the final component of the given name.  If such a beast
	     * is found, we concatenate the directory name and the final
	     * component and return the resulting string. If we don't find any
	     * such thing, we go on to phase two...
	     * 
	     * No matter what, we always look for the file in the current
	     * directory before anywhere else (unless we found the magic
	     * DOTLAST path, in which case we search it last) and we *do not*
	     * add the ./ to it if it exists.
	     * This is so there are no conflicts between what the user
	     * specifies (fish.c) and what pmake finds (./fish.c).
	     */
	    if (!hasLastDot &&
			(file = DirFindDot(hasSlash, name, cp)) != NULL) {
		    Lst_Close(path);
		    return file;
	    }

	    while ((ln = Lst_Next(path)) != NULL) {
		p = (Path *)Lst_Datum(ln);
		if (p == dotLast)
		    continue;
		if ((file = DirLookup(p, name, cp, hasSlash)) != NULL) {
		    Lst_Close(path);
		    return file;
		}
	    }

	    if (hasLastDot &&
			(file = DirFindDot(hasSlash, name, cp)) != NULL) {
		    Lst_Close(path);
		    return file;
	    }
    }
    Lst_Close(path);

    /*
     * We didn't find the file on any directory in the search path.
     * If the name doesn't contain a slash, that means it doesn't exist.
     * If it *does* contain a slash, however, there is still hope: it
     * could be in a subdirectory of one of the members of the search
     * path. (eg. /usr/include and sys/types.h. The above search would
     * fail to turn up types.h in /usr/include, but it *is* in
     * /usr/include/sys/types.h).
     * [ This no longer applies: If we find such a beast, we assume there
     * will be more (what else can we assume?) and add all but the last
     * component of the resulting name onto the search path (at the
     * end).]
     * This phase is only performed if the file is *not* absolute.
     */
    if (!hasSlash) {
	if (DEBUG(DIR)) {
	    fprintf(debug_file, "   failed.\n");
	}
	misses += 1;
	return NULL;
    }

    if (*cp == '\0') {
	/* we were given a trailing "/" */
	cp = trailing_dot;
    }

    if (name[0] != '/') {
	Boolean	checkedDot = FALSE;

	if (DEBUG(DIR)) {
	    fprintf(debug_file, "   Trying subdirectories...\n");
	}

	if (!hasLastDot) {
		if (dot) {
			checkedDot = TRUE;
			if ((file = DirLookupSubdir(dot, name)) != NULL)
				return file;
		}
		if (cur && (file = DirLookupSubdir(cur, name)) != NULL)
			return file;
	}

	(void)Lst_Open(path);
	while ((ln = Lst_Next(path)) != NULL) {
	    p = (Path *)Lst_Datum(ln);
	    if (p == dotLast)
		continue;
	    if (p == dot) {
		    if (checkedDot)
			    continue;
		checkedDot = TRUE;
	    }
	    if ((file = DirLookupSubdir(p, name)) != NULL) {
		Lst_Close(path);
		return file;
	    }
	}
	Lst_Close(path);

	if (hasLastDot) {
		if (dot && !checkedDot) {
			checkedDot = TRUE;
			if ((file = DirLookupSubdir(dot, name)) != NULL)
				return file;
		}
		if (cur && (file = DirLookupSubdir(cur, name)) != NULL)
			return file;
	}

	if (checkedDot) {
	    /*
	     * Already checked by the given name, since . was in the path,
	     * so no point in proceeding...
	     */
	    if (DEBUG(DIR)) {
		fprintf(debug_file, "   Checked . already, returning NULL\n");
	    }
	    return NULL;
	}

    } else { /* name[0] == '/' */

	/*
	 * For absolute names, compare directory path prefix against the
	 * the directory path of each member on the search path for an exact
	 * match. If we have an exact match on any member of the search path,
	 * use the cached contents of that member to lookup the final file
	 * component. If that lookup fails we can safely assume that the
	 * file does not exist at all.  This is signified by DirLookupAbs()
	 * returning an empty string.
	 */
	if (DEBUG(DIR)) {
	    fprintf(debug_file, "   Trying exact path matches...\n");
	}

	if (!hasLastDot && cur && ((file = DirLookupAbs(cur, name, cp))
		!= NULL)) {
	    if (file[0] == '\0') {
		free(file);
		return NULL;
	    }
	    return file;
	}

	(void)Lst_Open(path);
	while ((ln = Lst_Next(path)) != NULL) {
	    p = (Path *)Lst_Datum(ln);
	    if (p == dotLast)
		continue;
	    if ((file = DirLookupAbs(p, name, cp)) != NULL) {
		Lst_Close(path);
		if (file[0] == '\0') {
		    free(file);
		    return NULL;
		}
		return file;
	    }
	}
	Lst_Close(path);

	if (hasLastDot && cur && ((file = DirLookupAbs(cur, name, cp))
		!= NULL)) {
	    if (file[0] == '\0') {
		free(file);
		return NULL;
	    }
	    return file;
	}
    }

    /*
     * Didn't find it that way, either. Sigh. Phase 3. Add its directory
     * onto the search path in any case, just in case, then look for the
     * thing in the hash table. If we find it, grand. We return a new
     * copy of the name. Otherwise we sadly return a NULL pointer. Sigh.
     * Note that if the directory holding the file doesn't exist, this will
     * do an extra search of the final directory on the path. Unless something
     * weird happens, this search won't succeed and life will be groovy.
     *
     * Sigh. We cannot add the directory onto the search path because
     * of this amusing case:
     * $(INSTALLDIR)/$(FILE): $(FILE)
     *
     * $(FILE) exists in $(INSTALLDIR) but not in the current one.
     * When searching for $(FILE), we will find it in $(INSTALLDIR)
     * b/c we added it here. This is not good...
     */
#ifdef notdef
    if (cp == traling_dot) {
	cp = strrchr(name, '/');
	cp += 1;
    }
    cp[-1] = '\0';
    (void)Dir_AddDir(path, name);
    cp[-1] = '/';

    bigmisses += 1;
    ln = Lst_Last(path);
    if (ln == NULL) {
	return NULL;
    } else {
	p = (Path *)Lst_Datum(ln);
    }

    if (Hash_FindEntry(&p->files, cp) != NULL) {
	return (bmake_strdup(name));
    } else {
	return NULL;
    }
#else /* !notdef */
    if (DEBUG(DIR)) {
	fprintf(debug_file, "   Looking for \"%s\" ...\n", name);
    }

    bigmisses += 1;
    if (cached_stat(name, &stb) == 0) {
	return (bmake_strdup(name));
    }

    if (DEBUG(DIR)) {
	fprintf(debug_file, "   failed. Returning NULL\n");
    }
    return NULL;
#endif /* notdef */
}