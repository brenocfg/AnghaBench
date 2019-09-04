#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nSavepoint; TYPE_1__* aSavepoint; } ;
struct TYPE_4__ {scalar_t__ nOrig; int /*<<< orphan*/  pInSavepoint; } ;
typedef  scalar_t__ Pgno ;
typedef  TYPE_1__ PagerSavepoint ;
typedef  TYPE_2__ Pager ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3BitvecSet (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int addToSavepointBitvecs(Pager *pPager, Pgno pgno){
  int ii;                   /* Loop counter */
  int rc = SQLITE_OK;       /* Result code */

  for(ii=0; ii<pPager->nSavepoint; ii++){
    PagerSavepoint *p = &pPager->aSavepoint[ii];
    if( pgno<=p->nOrig ){
      rc |= sqlite3BitvecSet(p->pInSavepoint, pgno);
      testcase( rc==SQLITE_NOMEM );
      assert( rc==SQLITE_OK || rc==SQLITE_NOMEM );
    }
  }
  return rc;
}