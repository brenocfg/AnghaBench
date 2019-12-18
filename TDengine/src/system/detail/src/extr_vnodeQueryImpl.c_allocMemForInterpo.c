#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tFilePage ;
typedef  size_t int32_t ;
struct TYPE_14__ {int pointsPerFileBlock; } ;
struct TYPE_10__ {int /*<<< orphan*/ * pInterpoBuf; } ;
struct TYPE_13__ {TYPE_1__ runtimeEnv; } ;
struct TYPE_12__ {scalar_t__ interpoType; scalar_t__ nAggTimeInterval; int numOfOutputCols; TYPE_2__* pSelectExpr; } ;
struct TYPE_11__ {int resBytes; } ;
typedef  TYPE_3__ SQuery ;
typedef  TYPE_4__ SMeterQuerySupportObj ;
typedef  TYPE_5__ SMeterObj ;

/* Variables and functions */
 int POINTER_BYTES ; 
 scalar_t__ TSDB_INTERPO_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 scalar_t__ isPointInterpoQuery (TYPE_3__*) ; 
 int /*<<< orphan*/ * malloc (int) ; 

__attribute__((used)) static void allocMemForInterpo(SMeterQuerySupportObj *pSupporter, SQuery *pQuery, SMeterObj *pMeterObj) {
  if (pQuery->interpoType != TSDB_INTERPO_NONE) {
    assert(pQuery->nAggTimeInterval > 0 || (pQuery->nAggTimeInterval == 0 && isPointInterpoQuery(pQuery)));

    if (pQuery->nAggTimeInterval > 0) {
      pSupporter->runtimeEnv.pInterpoBuf = malloc(POINTER_BYTES * pQuery->numOfOutputCols);

      for (int32_t i = 0; i < pQuery->numOfOutputCols; ++i) {
        pSupporter->runtimeEnv.pInterpoBuf[i] =
            calloc(1, sizeof(tFilePage) + pQuery->pSelectExpr[i].resBytes * pMeterObj->pointsPerFileBlock);
      }
    }
  }
}