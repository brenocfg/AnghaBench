#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_6__ {TYPE_3__* db; int /*<<< orphan*/ * aVar; } ;
typedef  TYPE_1__ Vdbe ;
struct TYPE_7__ {int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  Mem ;

/* Variables and functions */
 int /*<<< orphan*/  ENC (TYPE_3__*) ; 
 int SQLITE_OK ; 
 void SQLITE_STATIC (void*) ; 
 void SQLITE_TRANSIENT (void*) ; 
 int sqlite3ApiExit (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sqlite3Error (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeChangeEncoding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeMemSetStr (int /*<<< orphan*/ *,void const*,int,scalar_t__,void (*) (void*)) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 
 int vdbeUnbind (TYPE_1__*,int) ; 

__attribute__((used)) static int bindText(
  sqlite3_stmt *pStmt,   /* The statement to bind against */
  int i,                 /* Index of the parameter to bind */
  const void *zData,     /* Pointer to the data to be bound */
  int nData,             /* Number of bytes of data to be bound */
  void (*xDel)(void*),   /* Destructor for the data */
  u8 encoding            /* Encoding for the data */
){
  Vdbe *p = (Vdbe *)pStmt;
  Mem *pVar;
  int rc;

  rc = vdbeUnbind(p, i);
  if( rc==SQLITE_OK ){
    if( zData!=0 ){
      pVar = &p->aVar[i-1];
      rc = sqlite3VdbeMemSetStr(pVar, zData, nData, encoding, xDel);
      if( rc==SQLITE_OK && encoding!=0 ){
        rc = sqlite3VdbeChangeEncoding(pVar, ENC(p->db));
      }
      sqlite3Error(p->db, rc, 0);
      rc = sqlite3ApiExit(p->db, rc);
    }
    sqlite3_mutex_leave(p->db->mutex);
  }else if( xDel!=SQLITE_STATIC && xDel!=SQLITE_TRANSIENT ){
    xDel((void*)zData);
  }
  return rc;
}