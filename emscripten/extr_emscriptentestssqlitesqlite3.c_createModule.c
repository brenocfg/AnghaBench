#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_module ;
struct TYPE_9__ {int mallocFailed; int /*<<< orphan*/  mutex; int /*<<< orphan*/  aModule; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_10__ {char* zName; void* pAux; void (* xDestroy ) (void*) ;int /*<<< orphan*/  const* pModule; } ;
typedef  TYPE_2__ Module ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_OK ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int sqlite3ApiExit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ sqlite3DbMallocRaw (TYPE_1__*,int) ; 
 scalar_t__ sqlite3HashInsert (int /*<<< orphan*/ *,char*,int,void*) ; 
 int /*<<< orphan*/  sqlite3ResetInternalSchema (TYPE_1__*,int) ; 
 int sqlite3Strlen30 (char const*) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 
 void stub1 (void*) ; 

__attribute__((used)) static int createModule(
  sqlite3 *db,                    /* Database in which module is registered */
  const char *zName,              /* Name assigned to this module */
  const sqlite3_module *pModule,  /* The definition of the module */
  void *pAux,                     /* Context pointer for xCreate/xConnect */
  void (*xDestroy)(void *)        /* Module destructor function */
){
  int rc, nName;
  Module *pMod;

  sqlite3_mutex_enter(db->mutex);
  nName = sqlite3Strlen30(zName);
  pMod = (Module *)sqlite3DbMallocRaw(db, sizeof(Module) + nName + 1);
  if( pMod ){
    Module *pDel;
    char *zCopy = (char *)(&pMod[1]);
    memcpy(zCopy, zName, nName+1);
    pMod->zName = zCopy;
    pMod->pModule = pModule;
    pMod->pAux = pAux;
    pMod->xDestroy = xDestroy;
    pDel = (Module *)sqlite3HashInsert(&db->aModule, zCopy, nName, (void*)pMod);
    if( pDel && pDel->xDestroy ){
      sqlite3ResetInternalSchema(db, -1);
      pDel->xDestroy(pDel->pAux);
    }
    sqlite3DbFree(db, pDel);
    if( pDel==pMod ){
      db->mallocFailed = 1;
    }
  }else if( xDestroy ){
    xDestroy(pAux);
  }
  rc = sqlite3ApiExit(db, SQLITE_OK);
  sqlite3_mutex_leave(db->mutex);
  return rc;
}