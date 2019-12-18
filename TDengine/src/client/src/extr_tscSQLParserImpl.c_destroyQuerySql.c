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
struct TYPE_4__ {int /*<<< orphan*/ * fillType; int /*<<< orphan*/ * from; int /*<<< orphan*/ * pGroupby; int /*<<< orphan*/ * pSortOrder; int /*<<< orphan*/ * pWhere; int /*<<< orphan*/ * pSelection; } ;
typedef  TYPE_1__ SQuerySQL ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  tSQLExprDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tSQLExprListDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tVariantListDestroy (int /*<<< orphan*/ *) ; 

void destroyQuerySql(SQuerySQL *pSql) {
  if (pSql == NULL) return;

  tSQLExprListDestroy(pSql->pSelection);
  pSql->pSelection = NULL;

  tSQLExprDestroy(pSql->pWhere);
  pSql->pWhere = NULL;

  tVariantListDestroy(pSql->pSortOrder);
  pSql->pSortOrder = NULL;

  tVariantListDestroy(pSql->pGroupby);
  pSql->pGroupby = NULL;

  tVariantListDestroy(pSql->from);
  pSql->from = NULL;

  tVariantListDestroy(pSql->fillType);

  free(pSql);
}