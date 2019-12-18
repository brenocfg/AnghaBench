#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {size_t vnodeIdx; } ;
struct TYPE_12__ {int /*<<< orphan*/  type; } ;
struct TYPE_13__ {struct TYPE_13__** pSubs; TYPE_1__ cmd; } ;
typedef  TYPE_2__ SSqlObj ;
typedef  TYPE_3__ SRetrieveSupport ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_QUERY_TYPE_STABLE_SUBQUERY ; 
 TYPE_2__* createSubqueryObj (TYPE_2__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  tscRetrieveDataRes ; 

__attribute__((used)) static SSqlObj *tscCreateSqlObjForSubquery(SSqlObj *pSql, SRetrieveSupport *trsupport, SSqlObj *prevSqlObj) {
  SSqlObj *pNew = createSubqueryObj(pSql, trsupport->vnodeIdx, 0, tscRetrieveDataRes, trsupport, prevSqlObj);
  if (pNew != NULL) {  // the sub query of two-stage super table query
    pNew->cmd.type |= TSDB_QUERY_TYPE_STABLE_SUBQUERY;
    pSql->pSubs[trsupport->vnodeIdx] = pNew;
  }

  return pNew;
}