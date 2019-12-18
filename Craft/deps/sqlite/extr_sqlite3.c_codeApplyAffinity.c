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
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_6__ {TYPE_1__* db; int /*<<< orphan*/ * pVdbe; } ;
struct TYPE_5__ {int mallocFailed; } ;
typedef  TYPE_2__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  OP_Affinity ; 
 char SQLITE_AFF_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3ExprCacheAffinityChange (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP4 (int /*<<< orphan*/ *,int,char*,int) ; 

__attribute__((used)) static void codeApplyAffinity(Parse *pParse, int base, int n, char *zAff){
  Vdbe *v = pParse->pVdbe;
  if( zAff==0 ){
    assert( pParse->db->mallocFailed );
    return;
  }
  assert( v!=0 );

  /* Adjust base and n to skip over SQLITE_AFF_NONE entries at the beginning
  ** and end of the affinity string.
  */
  while( n>0 && zAff[0]==SQLITE_AFF_NONE ){
    n--;
    base++;
    zAff++;
  }
  while( n>1 && zAff[n-1]==SQLITE_AFF_NONE ){
    n--;
  }

  /* Code the OP_Affinity opcode if there is anything left to do. */
  if( n>0 ){
    sqlite3VdbeAddOp2(v, OP_Affinity, base, n);
    sqlite3VdbeChangeP4(v, -1, zAff, n);
    sqlite3ExprCacheAffinityChange(pParse, base, n);
  }
}