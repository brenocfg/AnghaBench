#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_module ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  aModule; } ;
typedef  TYPE_1__ sqlite3 ;

/* Variables and functions */
 int SQLITE_MISUSE_BKPT ; 
 int SQLITE_OK ; 
 int sqlite3ApiExit (TYPE_1__*,int) ; 
 scalar_t__ sqlite3HashFind (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  sqlite3VtabCreateModule (TYPE_1__*,char const*,int /*<<< orphan*/  const*,void*,void (*) (void*)) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int createModule(
  sqlite3 *db,                    /* Database in which module is registered */
  const char *zName,              /* Name assigned to this module */
  const sqlite3_module *pModule,  /* The definition of the module */
  void *pAux,                     /* Context pointer for xCreate/xConnect */
  void (*xDestroy)(void *)        /* Module destructor function */
){
  int rc = SQLITE_OK;

  sqlite3_mutex_enter(db->mutex);
  if( sqlite3HashFind(&db->aModule, zName) ){
    rc = SQLITE_MISUSE_BKPT;
  }else{
    (void)sqlite3VtabCreateModule(db, zName, pModule, pAux, xDestroy);
  }
  rc = sqlite3ApiExit(db, rc);
  if( rc!=SQLITE_OK && xDestroy ) xDestroy(pAux);
  sqlite3_mutex_leave(db->mutex);
  return rc;
}