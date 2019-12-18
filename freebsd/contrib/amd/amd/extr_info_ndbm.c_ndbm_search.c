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
typedef  scalar_t__ time_t ;
struct stat {scalar_t__ st_mtime; } ;
typedef  int /*<<< orphan*/  mnt_map ;
typedef  int /*<<< orphan*/  dbfilename ;
typedef  int /*<<< orphan*/  DBM ;

/* Variables and functions */
 int /*<<< orphan*/  DBM_SUFFIX ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  dbm_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbm_open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbm_pagfno (int /*<<< orphan*/ *) ; 
 int errno ; 
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int search_ndbm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  xstrlcat (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xstrlcpy (char*,char*,int) ; 

int
ndbm_search(mnt_map *m, char *map, char *key, char **pval, time_t *tp)
{
  DBM *db;

  db = dbm_open(map, O_RDONLY, 0);
  if (db) {
    struct stat stb;
    int error;
#ifdef DBM_SUFFIX
    char dbfilename[256];

    xstrlcpy(dbfilename, map, sizeof(dbfilename));
    xstrlcat(dbfilename, DBM_SUFFIX, sizeof(dbfilename));
    error = stat(dbfilename, &stb);
#else /* not DBM_SUFFIX */
    error = fstat(dbm_pagfno(db), &stb);
#endif /* not DBM_SUFFIX */
    if (!error && *tp < stb.st_mtime) {
      *tp = stb.st_mtime;
      error = -1;
    } else {
      error = search_ndbm(m, db, key, pval);
    }
    (void) dbm_close(db);
    return error;
  }
  return errno;
}