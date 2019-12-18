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
typedef  int /*<<< orphan*/  i64 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_7__ {int iValue; char* zToken; } ;
struct TYPE_9__ {int flags; TYPE_1__ u; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pVdbe; } ;
typedef  TYPE_2__ Parse ;
typedef  TYPE_3__ Expr ;

/* Variables and functions */
 int EP_IntValue ; 
 int /*<<< orphan*/  OP_Int64 ; 
 int /*<<< orphan*/  OP_Integer ; 
 int /*<<< orphan*/  P4_INT64 ; 
 int /*<<< orphan*/  SMALLEST_INT64 ; 
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  codeReal (int /*<<< orphan*/ *,char const*,int,int) ; 
 char* dup8bytes (int /*<<< orphan*/ *,char*) ; 
 int sqlite3Atoi64 (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_2__*,char*,char*,char const*) ; 
 int /*<<< orphan*/  sqlite3Strlen30 (char const*) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void codeInteger(Parse *pParse, Expr *pExpr, int negFlag, int iMem){
  Vdbe *v = pParse->pVdbe;
  if( pExpr->flags & EP_IntValue ){
    int i = pExpr->u.iValue;
    assert( i>=0 );
    if( negFlag ) i = -i;
    sqlite3VdbeAddOp2(v, OP_Integer, i, iMem);
  }else{
    int c;
    i64 value;
    const char *z = pExpr->u.zToken;
    assert( z!=0 );
    c = sqlite3Atoi64(z, &value, sqlite3Strlen30(z), SQLITE_UTF8);
    if( c==0 || (c==2 && negFlag) ){
      char *zV;
      if( negFlag ){ value = c==2 ? SMALLEST_INT64 : -value; }
      zV = dup8bytes(v, (char*)&value);
      sqlite3VdbeAddOp4(v, OP_Int64, 0, iMem, 0, zV, P4_INT64);
    }else{
#ifdef SQLITE_OMIT_FLOATING_POINT
      sqlite3ErrorMsg(pParse, "oversized integer: %s%s", negFlag ? "-" : "", z);
#else
      codeReal(v, z, negFlag, iMem);
#endif
    }
  }
}