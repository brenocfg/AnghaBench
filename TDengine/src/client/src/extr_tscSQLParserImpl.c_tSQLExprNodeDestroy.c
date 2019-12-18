#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ nSQLOptr; int /*<<< orphan*/  pParam; int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ tSQLExpr ;

/* Variables and functions */
 scalar_t__ TK_STRING ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  tSQLExprListDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tVariantDestroy (int /*<<< orphan*/ *) ; 

void tSQLExprNodeDestroy(tSQLExpr *pExpr) {
  if (pExpr == NULL) {
    return;
  }

  if (pExpr->nSQLOptr == TK_STRING) {
    tVariantDestroy(&pExpr->val);
  }

  tSQLExprListDestroy(pExpr->pParam);

  free(pExpr);
}