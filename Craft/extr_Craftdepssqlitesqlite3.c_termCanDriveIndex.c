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
struct SrcList_item {scalar_t__ iCursor; TYPE_1__* pTab; } ;
struct TYPE_7__ {size_t leftColumn; } ;
struct TYPE_9__ {scalar_t__ leftCursor; int eOperator; int prereqRight; int /*<<< orphan*/  pExpr; TYPE_2__ u; } ;
typedef  TYPE_4__ WhereTerm ;
struct TYPE_8__ {char affinity; } ;
struct TYPE_6__ {TYPE_3__* aCol; } ;
typedef  int Bitmask ;

/* Variables and functions */
 int WO_EQ ; 
 int /*<<< orphan*/  sqlite3IndexAffinityOk (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static int termCanDriveIndex(
  WhereTerm *pTerm,              /* WHERE clause term to check */
  struct SrcList_item *pSrc,     /* Table we are trying to access */
  Bitmask notReady               /* Tables in outer loops of the join */
){
  char aff;
  if( pTerm->leftCursor!=pSrc->iCursor ) return 0;
  if( (pTerm->eOperator & WO_EQ)==0 ) return 0;
  if( (pTerm->prereqRight & notReady)!=0 ) return 0;
  aff = pSrc->pTab->aCol[pTerm->u.leftColumn].affinity;
  if( !sqlite3IndexAffinityOk(pTerm->pExpr, aff) ) return 0;
  return 1;
}