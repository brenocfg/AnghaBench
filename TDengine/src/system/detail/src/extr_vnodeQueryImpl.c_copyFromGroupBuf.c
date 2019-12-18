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
typedef  scalar_t__ int32_t ;
struct TYPE_6__ {scalar_t__ pointsRead; scalar_t__ pointsToRead; TYPE_1__* pGroupbyExpr; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pMeterQuerySupporter; TYPE_2__ query; } ;
struct TYPE_5__ {scalar_t__ orderType; } ;
typedef  TYPE_2__ SQuery ;
typedef  TYPE_3__ SQInfo ;
typedef  int /*<<< orphan*/  SOutputRes ;
typedef  int /*<<< orphan*/  SMeterQuerySupportObj ;

/* Variables and functions */
 scalar_t__ TSQL_SO_DESC ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ doCopyFromGroupBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

void copyFromGroupBuf(SQInfo *pQInfo, SOutputRes *result) {
  SQuery *               pQuery = &pQInfo->query;
  SMeterQuerySupportObj *pSupporter = pQInfo->pMeterQuerySupporter;

  int32_t orderType = (pQuery->pGroupbyExpr != NULL) ? pQuery->pGroupbyExpr->orderType : TSQL_SO_DESC;

  int32_t numOfResult = doCopyFromGroupBuf(pSupporter, result, orderType);

  pQuery->pointsRead += numOfResult;
  assert(pQuery->pointsRead <= pQuery->pointsToRead);
}