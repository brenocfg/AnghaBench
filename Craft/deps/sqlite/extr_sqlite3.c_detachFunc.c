#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zErr ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_5__ {int nDb; int /*<<< orphan*/  autoCommit; TYPE_2__* aDb; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_6__ {scalar_t__ pBt; scalar_t__ pSchema; int /*<<< orphan*/  zName; } ;
typedef  TYPE_2__ Db ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  sqlite3BtreeClose (scalar_t__) ; 
 scalar_t__ sqlite3BtreeIsInBackup (scalar_t__) ; 
 scalar_t__ sqlite3BtreeIsInReadTrans (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3ResetAllSchemasOfConnection (TYPE_1__*) ; 
 scalar_t__ sqlite3StrICmp (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* sqlite3_context_db_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,...) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void detachFunc(
  sqlite3_context *context,
  int NotUsed,
  sqlite3_value **argv
){
  const char *zName = (const char *)sqlite3_value_text(argv[0]);
  sqlite3 *db = sqlite3_context_db_handle(context);
  int i;
  Db *pDb = 0;
  char zErr[128];

  UNUSED_PARAMETER(NotUsed);

  if( zName==0 ) zName = "";
  for(i=0; i<db->nDb; i++){
    pDb = &db->aDb[i];
    if( pDb->pBt==0 ) continue;
    if( sqlite3StrICmp(pDb->zName, zName)==0 ) break;
  }

  if( i>=db->nDb ){
    sqlite3_snprintf(sizeof(zErr),zErr, "no such database: %s", zName);
    goto detach_error;
  }
  if( i<2 ){
    sqlite3_snprintf(sizeof(zErr),zErr, "cannot detach database %s", zName);
    goto detach_error;
  }
  if( !db->autoCommit ){
    sqlite3_snprintf(sizeof(zErr), zErr,
                     "cannot DETACH database within transaction");
    goto detach_error;
  }
  if( sqlite3BtreeIsInReadTrans(pDb->pBt) || sqlite3BtreeIsInBackup(pDb->pBt) ){
    sqlite3_snprintf(sizeof(zErr),zErr, "database %s is locked", zName);
    goto detach_error;
  }

  sqlite3BtreeClose(pDb->pBt);
  pDb->pBt = 0;
  pDb->pSchema = 0;
  sqlite3ResetAllSchemasOfConnection(db);
  return;

detach_error:
  sqlite3_result_error(context, zErr, -1);
}