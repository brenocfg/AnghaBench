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
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sqlite3_index_constraint {scalar_t__ usable; scalar_t__ op; scalar_t__ iColumn; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_6__ {double estimatedCost; int nConstraint; int estimatedRows; TYPE_1__* aConstraintUsage; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_2__ sqlite3_index_info ;
struct TYPE_7__ {scalar_t__ nHidden; scalar_t__ iHidden; } ;
struct TYPE_5__ {int argvIndex; int omit; } ;
typedef  TYPE_3__ PragmaVtab ;

/* Variables and functions */
 scalar_t__ SQLITE_INDEX_CONSTRAINT_EQ ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int pragmaVtabBestIndex(sqlite3_vtab *tab, sqlite3_index_info *pIdxInfo){
  PragmaVtab *pTab = (PragmaVtab*)tab;
  const struct sqlite3_index_constraint *pConstraint;
  int i, j;
  int seen[2];

  pIdxInfo->estimatedCost = (double)1;
  if( pTab->nHidden==0 ){ return SQLITE_OK; }
  pConstraint = pIdxInfo->aConstraint;
  seen[0] = 0;
  seen[1] = 0;
  for(i=0; i<pIdxInfo->nConstraint; i++, pConstraint++){
    if( pConstraint->usable==0 ) continue;
    if( pConstraint->op!=SQLITE_INDEX_CONSTRAINT_EQ ) continue;
    if( pConstraint->iColumn < pTab->iHidden ) continue;
    j = pConstraint->iColumn - pTab->iHidden;
    assert( j < 2 );
    seen[j] = i+1;
  }
  if( seen[0]==0 ){
    pIdxInfo->estimatedCost = (double)2147483647;
    pIdxInfo->estimatedRows = 2147483647;
    return SQLITE_OK;
  }
  j = seen[0]-1;
  pIdxInfo->aConstraintUsage[j].argvIndex = 1;
  pIdxInfo->aConstraintUsage[j].omit = 1;
  if( seen[1]==0 ) return SQLITE_OK;
  pIdxInfo->estimatedCost = (double)20;
  pIdxInfo->estimatedRows = 20;
  j = seen[1]-1;
  pIdxInfo->aConstraintUsage[j].argvIndex = 2;
  pIdxInfo->aConstraintUsage[j].omit = 1;
  return SQLITE_OK;
}