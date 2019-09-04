#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  mallocFailed; } ;
typedef  TYPE_1__ sqlite3 ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_UTF16NATIVE ; 
 int /*<<< orphan*/  assert (int) ; 
 int createCollation (TYPE_1__*,char*,int /*<<< orphan*/ ,void*,int (*) (void*,int,void const*,int,void const*),int /*<<< orphan*/ ) ; 
 int sqlite3ApiExit (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_1__*,char*) ; 
 char* sqlite3Utf16to8 (TYPE_1__*,void const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 

int sqlite3_create_collation16(
  sqlite3* db, 
  const void *zName,
  int enc, 
  void* pCtx,
  int(*xCompare)(void*,int,const void*,int,const void*)
){
  int rc = SQLITE_OK;
  char *zName8;
  sqlite3_mutex_enter(db->mutex);
  assert( !db->mallocFailed );
  zName8 = sqlite3Utf16to8(db, zName, -1, SQLITE_UTF16NATIVE);
  if( zName8 ){
    rc = createCollation(db, zName8, (u8)enc, pCtx, xCompare, 0);
    sqlite3DbFree(db, zName8);
  }
  rc = sqlite3ApiExit(db, rc);
  sqlite3_mutex_leave(db->mutex);
  return rc;
}