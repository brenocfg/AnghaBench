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
struct TYPE_5__ {int numOfGroups; } ;
struct TYPE_6__ {TYPE_1__ res; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_1__ SSqlRes ;
typedef  TYPE_2__ SSqlObj ;
typedef  int /*<<< orphan*/  SSqlCmd ;

/* Variables and functions */
 scalar_t__ reachGroupResultLimit (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static bool saveGroupResultInfo(SSqlObj *pSql) {
  SSqlCmd *pCmd = &pSql->cmd;
  SSqlRes *pRes = &pSql->res;

  pRes->numOfGroups += 1;

  // the output group is limited by the slimit clause
  if (reachGroupResultLimit(pCmd, pRes)) {
    return true;
  }

  //    pRes->pGroupRec = realloc(pRes->pGroupRec, pRes->numOfGroups*sizeof(SResRec));
  //    pRes->pGroupRec[pRes->numOfGroups-1].numOfRows = pRes->numOfRows;
  //    pRes->pGroupRec[pRes->numOfGroups-1].numOfTotal = pRes->numOfTotal;

  return false;
}