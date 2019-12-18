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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  usedIndex; TYPE_3__* pQuery; } ;
struct TYPE_9__ {TYPE_2__* pSidSet; TYPE_1__ runtimeEnv; } ;
struct TYPE_8__ {int /*<<< orphan*/  pGroupbyExpr; } ;
struct TYPE_7__ {int /*<<< orphan*/  numOfSubSet; } ;
typedef  TYPE_3__ SQuery ;
typedef  TYPE_4__ SMeterQuerySupportObj ;

/* Variables and functions */
 scalar_t__ isGroupbyNormalCol (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t getSubsetNumber(SMeterQuerySupportObj *pSupporter) {
  SQuery *pQuery = pSupporter->runtimeEnv.pQuery;

  int32_t totalSubset = 0;
  if (isGroupbyNormalCol(pQuery->pGroupbyExpr)) {
    totalSubset = pSupporter->runtimeEnv.usedIndex;
  } else {
    totalSubset = pSupporter->pSidSet->numOfSubSet;
  }

  return totalSubset;
}