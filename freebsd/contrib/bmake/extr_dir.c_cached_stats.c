#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_mtime; int /*<<< orphan*/  st_mode; } ;
struct cache_st {int mtime; int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {struct cache_st* clientPtr; } ;
typedef  int /*<<< orphan*/  Hash_Table ;
typedef  TYPE_1__ Hash_Entry ;

/* Variables and functions */
 int CST_LSTAT ; 
 int CST_UPDATE ; 
 scalar_t__ DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIR ; 
 TYPE_1__* Hash_CreateEntry (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* Hash_FindEntry (int /*<<< orphan*/ *,char const*) ; 
 char* Targ_FmtTime (int) ; 
 struct cache_st* bmake_malloc (int) ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int lstat (char const*,struct stat*) ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 
 int stat (char const*,struct stat*) ; 

__attribute__((used)) static int
cached_stats(Hash_Table *htp, const char *pathname, struct stat *st, int flags)
{
    Hash_Entry *entry;
    struct cache_st *cst;
    int rc;

    if (!pathname || !pathname[0])
	return -1;

    entry = Hash_FindEntry(htp, pathname);

    if (entry && (flags & CST_UPDATE) == 0) {
	cst = entry->clientPtr;

	memset(st, 0, sizeof(*st));
	st->st_mtime = cst->mtime;
	st->st_mode = cst->mode;
        if (DEBUG(DIR)) {
            fprintf(debug_file, "Using cached time %s for %s\n",
		Targ_FmtTime(st->st_mtime), pathname);
	}
	return 0;
    }

    rc = (flags & CST_LSTAT) ? lstat(pathname, st) : stat(pathname, st);
    if (rc == -1)
	return -1;

    if (st->st_mtime == 0)
	st->st_mtime = 1;      /* avoid confusion with missing file */

    if (!entry)
	entry = Hash_CreateEntry(htp, pathname, NULL);
    if (!entry->clientPtr)
	entry->clientPtr = bmake_malloc(sizeof(*cst));
    cst = entry->clientPtr;
    cst->mtime = st->st_mtime;
    cst->mode = st->st_mode;
    if (DEBUG(DIR)) {
	fprintf(debug_file, "   Caching %s for %s\n",
	    Targ_FmtTime(st->st_mtime), pathname);
    }

    return 0;
}