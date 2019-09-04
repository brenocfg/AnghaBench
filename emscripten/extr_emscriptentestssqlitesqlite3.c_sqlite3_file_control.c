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
struct TYPE_8__ {scalar_t__ pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
struct TYPE_9__ {int nDb; int /*<<< orphan*/  mutex; TYPE_1__* aDb; } ;
typedef  TYPE_3__ sqlite3 ;
struct TYPE_7__ {int /*<<< orphan*/ * pBt; int /*<<< orphan*/  zName; } ;
typedef  int /*<<< orphan*/  Pager ;
typedef  int /*<<< orphan*/  Btree ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_FCNTL_FILE_POINTER ; 
 int SQLITE_NOTFOUND ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3BtreeEnter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3BtreeLeave (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3BtreePager (int /*<<< orphan*/ *) ; 
 int sqlite3OsFileControl (TYPE_2__*,int,void*) ; 
 TYPE_2__* sqlite3PagerFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int sqlite3_file_control(sqlite3 *db, const char *zDbName, int op, void *pArg){
  int rc = SQLITE_ERROR;
  int iDb;
  sqlite3_mutex_enter(db->mutex);
  if( zDbName==0 ){
    iDb = 0;
  }else{
    for(iDb=0; iDb<db->nDb; iDb++){
      if( strcmp(db->aDb[iDb].zName, zDbName)==0 ) break;
    }
  }
  if( iDb<db->nDb ){
    Btree *pBtree = db->aDb[iDb].pBt;
    if( pBtree ){
      Pager *pPager;
      sqlite3_file *fd;
      sqlite3BtreeEnter(pBtree);
      pPager = sqlite3BtreePager(pBtree);
      assert( pPager!=0 );
      fd = sqlite3PagerFile(pPager);
      assert( fd!=0 );
      if( op==SQLITE_FCNTL_FILE_POINTER ){
        *(sqlite3_file**)pArg = fd;
        rc = SQLITE_OK;
      }else if( fd->pMethods ){
        rc = sqlite3OsFileControl(fd, op, pArg);
      }else{
        rc = SQLITE_NOTFOUND;
      }
      sqlite3BtreeLeave(pBtree);
    }
  }
  sqlite3_mutex_leave(db->mutex);
  return rc;   
}