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
struct TYPE_5__ {int /*<<< orphan*/  nZero; int /*<<< orphan*/  r; int /*<<< orphan*/  i; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  enc; int /*<<< orphan*/  n; int /*<<< orphan*/  z; TYPE_1__ u; } ;
typedef  TYPE_2__ sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;

/* Variables and functions */
 int MEM_Zero ; 
#define  SQLITE_BLOB 131 
#define  SQLITE_FLOAT 130 
#define  SQLITE_INTEGER 129 
#define  SQLITE_TEXT 128 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int bindText (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3_bind_blob (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3_bind_double (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int sqlite3_bind_int64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int sqlite3_bind_null (int /*<<< orphan*/ *,int) ; 
 int sqlite3_bind_zeroblob (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int sqlite3_value_type (TYPE_2__*) ; 

int sqlite3_bind_value(sqlite3_stmt *pStmt, int i, const sqlite3_value *pValue){
  int rc;
  switch( sqlite3_value_type((sqlite3_value*)pValue) ){
    case SQLITE_INTEGER: {
      rc = sqlite3_bind_int64(pStmt, i, pValue->u.i);
      break;
    }
    case SQLITE_FLOAT: {
      rc = sqlite3_bind_double(pStmt, i, pValue->u.r);
      break;
    }
    case SQLITE_BLOB: {
      if( pValue->flags & MEM_Zero ){
        rc = sqlite3_bind_zeroblob(pStmt, i, pValue->u.nZero);
      }else{
        rc = sqlite3_bind_blob(pStmt, i, pValue->z, pValue->n,SQLITE_TRANSIENT);
      }
      break;
    }
    case SQLITE_TEXT: {
      rc = bindText(pStmt,i,  pValue->z, pValue->n, SQLITE_TRANSIENT,
                              pValue->enc);
      break;
    }
    default: {
      rc = sqlite3_bind_null(pStmt, i);
      break;
    }
  }
  return rc;
}