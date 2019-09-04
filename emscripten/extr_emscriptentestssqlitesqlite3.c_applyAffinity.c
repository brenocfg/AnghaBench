#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int flags; } ;
typedef  TYPE_1__ Mem ;

/* Variables and functions */
 int MEM_Int ; 
 int MEM_Real ; 
 int MEM_Str ; 
 char SQLITE_AFF_INTEGER ; 
 char SQLITE_AFF_NONE ; 
 char SQLITE_AFF_NUMERIC ; 
 char SQLITE_AFF_REAL ; 
 char SQLITE_AFF_TEXT ; 
 int /*<<< orphan*/  applyNumericAffinity (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3VdbeIntegerAffinity (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3VdbeMemStringify (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void applyAffinity(
  Mem *pRec,          /* The value to apply affinity to */
  char affinity,      /* The affinity to be applied */
  u8 enc              /* Use this text encoding */
){
  if( affinity==SQLITE_AFF_TEXT ){
    /* Only attempt the conversion to TEXT if there is an integer or real
    ** representation (blob and NULL do not get converted) but no string
    ** representation.
    */
    if( 0==(pRec->flags&MEM_Str) && (pRec->flags&(MEM_Real|MEM_Int)) ){
      sqlite3VdbeMemStringify(pRec, enc);
    }
    pRec->flags &= ~(MEM_Real|MEM_Int);
  }else if( affinity!=SQLITE_AFF_NONE ){
    assert( affinity==SQLITE_AFF_INTEGER || affinity==SQLITE_AFF_REAL
             || affinity==SQLITE_AFF_NUMERIC );
    applyNumericAffinity(pRec);
    if( pRec->flags & MEM_Real ){
      sqlite3VdbeIntegerAffinity(pRec);
    }
  }
}