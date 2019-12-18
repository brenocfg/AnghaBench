#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  scalar_t__ tRowcnt ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_6__ {int* anDLt; int* anEq; } ;
struct TYPE_9__ {int nKeyCol; int nRow; scalar_t__ iGet; scalar_t__ nSample; int nCol; TYPE_3__* a; TYPE_1__ current; } ;
struct TYPE_7__ {int /*<<< orphan*/  aRowid; int /*<<< orphan*/  iRowid; } ;
struct TYPE_8__ {scalar_t__ nRowid; scalar_t__* anDLt; scalar_t__* anLt; scalar_t__* anEq; TYPE_2__ u; } ;
typedef  TYPE_3__ Stat4Sample ;
typedef  TYPE_4__ Stat4Accum ;

/* Variables and functions */
 scalar_t__ IsStat3 ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int STAT_GET_NDLT ; 
#define  STAT_GET_NEQ 129 
#define  STAT_GET_NLT 128 
 int STAT_GET_ROWID ; 
 int STAT_GET_STAT1 ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  samplePushPrevious (TYPE_4__*,int /*<<< orphan*/ ) ; 
 char* sqlite3MallocZero (int) ; 
 int sqlite3Strlen30 (char*) ; 
 int /*<<< orphan*/  sqlite3_free ; 
 int /*<<< orphan*/  sqlite3_result_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int) ; 
 scalar_t__ sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int sqlite3_value_int (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void statGet(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  Stat4Accum *p = (Stat4Accum*)sqlite3_value_blob(argv[0]);
#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
  /* STAT3 and STAT4 have a parameter on this routine. */
  int eCall = sqlite3_value_int(argv[1]);
  assert( argc==2 );
  assert( eCall==STAT_GET_STAT1 || eCall==STAT_GET_NEQ 
       || eCall==STAT_GET_ROWID || eCall==STAT_GET_NLT
       || eCall==STAT_GET_NDLT 
  );
  if( eCall==STAT_GET_STAT1 )
#else
  assert( argc==1 );
#endif
  {
    /* Return the value to store in the "stat" column of the sqlite_stat1
    ** table for this index.
    **
    ** The value is a string composed of a list of integers describing 
    ** the index. The first integer in the list is the total number of 
    ** entries in the index. There is one additional integer in the list 
    ** for each indexed column. This additional integer is an estimate of
    ** the number of rows matched by a stabbing query on the index using
    ** a key with the corresponding number of fields. In other words,
    ** if the index is on columns (a,b) and the sqlite_stat1 value is 
    ** "100 10 2", then SQLite estimates that:
    **
    **   * the index contains 100 rows,
    **   * "WHERE a=?" matches 10 rows, and
    **   * "WHERE a=? AND b=?" matches 2 rows.
    **
    ** If D is the count of distinct values and K is the total number of 
    ** rows, then each estimate is computed as:
    **
    **        I = (K+D-1)/D
    */
    char *z;
    int i;

    char *zRet = sqlite3MallocZero( (p->nKeyCol+1)*25 );
    if( zRet==0 ){
      sqlite3_result_error_nomem(context);
      return;
    }

    sqlite3_snprintf(24, zRet, "%llu", (u64)p->nRow);
    z = zRet + sqlite3Strlen30(zRet);
    for(i=0; i<p->nKeyCol; i++){
      u64 nDistinct = p->current.anDLt[i] + 1;
      u64 iVal = (p->nRow + nDistinct - 1) / nDistinct;
      sqlite3_snprintf(24, z, " %llu", iVal);
      z += sqlite3Strlen30(z);
      assert( p->current.anEq[i] );
    }
    assert( z[0]=='\0' && z>zRet );

    sqlite3_result_text(context, zRet, -1, sqlite3_free);
  }
#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
  else if( eCall==STAT_GET_ROWID ){
    if( p->iGet<0 ){
      samplePushPrevious(p, 0);
      p->iGet = 0;
    }
    if( p->iGet<p->nSample ){
      Stat4Sample *pS = p->a + p->iGet;
      if( pS->nRowid==0 ){
        sqlite3_result_int64(context, pS->u.iRowid);
      }else{
        sqlite3_result_blob(context, pS->u.aRowid, pS->nRowid,
                            SQLITE_TRANSIENT);
      }
    }
  }else{
    tRowcnt *aCnt = 0;

    assert( p->iGet<p->nSample );
    switch( eCall ){
      case STAT_GET_NEQ:  aCnt = p->a[p->iGet].anEq; break;
      case STAT_GET_NLT:  aCnt = p->a[p->iGet].anLt; break;
      default: {
        aCnt = p->a[p->iGet].anDLt; 
        p->iGet++;
        break;
      }
    }

    if( IsStat3 ){
      sqlite3_result_int64(context, (i64)aCnt[0]);
    }else{
      char *zRet = sqlite3MallocZero(p->nCol * 25);
      if( zRet==0 ){
        sqlite3_result_error_nomem(context);
      }else{
        int i;
        char *z = zRet;
        for(i=0; i<p->nCol; i++){
          sqlite3_snprintf(24, z, "%llu ", (u64)aCnt[i]);
          z += sqlite3Strlen30(z);
        }
        assert( z[0]=='\0' && z>zRet );
        z[-1] = '\0';
        sqlite3_result_text(context, zRet, -1, sqlite3_free);
      }
    }
  }
#endif /* SQLITE_ENABLE_STAT3_OR_STAT4 */
#ifndef SQLITE_DEBUG
  UNUSED_PARAMETER( argc );
#endif
}