#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* cfm; } ;
typedef  TYPE_2__ mnt_map ;
struct TYPE_9__ {char* dptr; scalar_t__ dsize; } ;
typedef  TYPE_3__ datum ;
struct TYPE_7__ {int cfm_flags; } ;
typedef  int /*<<< orphan*/  DBM ;

/* Variables and functions */
 int CFM_SUN_MAP_SYNTAX ; 
 int ENOENT ; 
 TYPE_3__ dbm_fetch (int /*<<< orphan*/ *,TYPE_3__) ; 
 scalar_t__ strlen (char*) ; 
 char* sun_entry2amd (char*,char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static int
search_ndbm(mnt_map *m, DBM *db, char *key, char **val)
{
  datum k, v;

  k.dptr = key;
  k.dsize = strlen(key) + 1;
  v = dbm_fetch(db, k);
  if (v.dptr) {
    if (m->cfm && (m->cfm->cfm_flags & CFM_SUN_MAP_SYNTAX))
      *val = sun_entry2amd(key, v.dptr);
    else
      *val = xstrdup(v.dptr);
    return 0;
  }
  return ENOENT;
}