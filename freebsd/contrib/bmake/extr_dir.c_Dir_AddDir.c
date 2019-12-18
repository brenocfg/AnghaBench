#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct dirent {scalar_t__ d_fileno; int /*<<< orphan*/  d_name; } ;
struct TYPE_9__ {int refCount; } ;
struct TYPE_8__ {int refCount; int /*<<< orphan*/  files; scalar_t__ hits; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ Path ;
typedef  int /*<<< orphan*/ * LstNode ;
typedef  int /*<<< orphan*/ * Lst ;

/* Variables and functions */
 scalar_t__ DEBUG (int) ; 
 int DIR ; 
 int /*<<< orphan*/  DirFindName ; 
 int /*<<< orphan*/  Hash_CreateEntry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Hash_InitTable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Lst_AtEnd (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Lst_AtFront (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ Lst_Datum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Lst_Find (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Lst_Member (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* bmake_malloc (int) ; 
 int /*<<< orphan*/  bmake_strdup (char const*) ; 
 int /*<<< orphan*/  closedir (int) ; 
 int d ; 
 int /*<<< orphan*/  debug_file ; 
 TYPE_2__* dotLast ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * openDirectories ; 
 int /*<<< orphan*/  opendir (char const*) ; 
 struct dirent* readdir (int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

Path *
Dir_AddDir(Lst path, const char *name)
{
    LstNode       ln = NULL; /* node in case Path structure is found */
    Path	  *p = NULL;  /* pointer to new Path structure */
    DIR     	  *d;	      /* for reading directory */
    struct dirent *dp;	      /* entry in directory */

    if (strcmp(name, ".DOTLAST") == 0) {
	ln = Lst_Find(path, name, DirFindName);
	if (ln != NULL)
	    return (Path *)Lst_Datum(ln);
	else {
	    dotLast->refCount += 1;
	    (void)Lst_AtFront(path, dotLast);
	}
    }

    if (path)
	ln = Lst_Find(openDirectories, name, DirFindName);
    if (ln != NULL) {
	p = (Path *)Lst_Datum(ln);
	if (path && Lst_Member(path, p) == NULL) {
	    p->refCount += 1;
	    (void)Lst_AtEnd(path, p);
	}
    } else {
	if (DEBUG(DIR)) {
	    fprintf(debug_file, "Caching %s ...", name);
	}

	if ((d = opendir(name)) != NULL) {
	    p = bmake_malloc(sizeof(Path));
	    p->name = bmake_strdup(name);
	    p->hits = 0;
	    p->refCount = 1;
	    Hash_InitTable(&p->files, -1);

	    while ((dp = readdir(d)) != NULL) {
#if defined(sun) && defined(d_ino) /* d_ino is a sunos4 #define for d_fileno */
		/*
		 * The sun directory library doesn't check for a 0 inode
		 * (0-inode slots just take up space), so we have to do
		 * it ourselves.
		 */
		if (dp->d_fileno == 0) {
		    continue;
		}
#endif /* sun && d_ino */
		(void)Hash_CreateEntry(&p->files, dp->d_name, NULL);
	    }
	    (void)closedir(d);
	    (void)Lst_AtEnd(openDirectories, p);
	    if (path != NULL)
		(void)Lst_AtEnd(path, p);
	}
	if (DEBUG(DIR)) {
	    fprintf(debug_file, "done\n");
	}
    }
    return p;
}