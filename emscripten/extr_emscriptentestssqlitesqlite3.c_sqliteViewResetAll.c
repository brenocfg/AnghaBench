#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* aDb; } ;
typedef  TYPE_3__ sqlite3 ;
struct TYPE_15__ {scalar_t__ nCol; scalar_t__ aCol; scalar_t__ pSelect; } ;
typedef  TYPE_4__ Table ;
struct TYPE_13__ {TYPE_1__* pSchema; } ;
struct TYPE_12__ {int /*<<< orphan*/  tblHash; } ;
typedef  int /*<<< orphan*/  HashElem ;

/* Variables and functions */
 int /*<<< orphan*/  DB_UnresetViews ; 
 int /*<<< orphan*/  DbClearProperty (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DbHasProperty (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SchemaMutexHeld (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqliteDeleteColumnNames (TYPE_3__*,TYPE_4__*) ; 
 TYPE_4__* sqliteHashData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqliteHashFirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqliteHashNext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sqliteViewResetAll(sqlite3 *db, int idx){
  HashElem *i;
  assert( sqlite3SchemaMutexHeld(db, idx, 0) );
  if( !DbHasProperty(db, idx, DB_UnresetViews) ) return;
  for(i=sqliteHashFirst(&db->aDb[idx].pSchema->tblHash); i;i=sqliteHashNext(i)){
    Table *pTab = sqliteHashData(i);
    if( pTab->pSelect ){
      sqliteDeleteColumnNames(db, pTab);
      pTab->aCol = 0;
      pTab->nCol = 0;
    }
  }
  DbClearProperty(db, idx, DB_UnresetViews);
}