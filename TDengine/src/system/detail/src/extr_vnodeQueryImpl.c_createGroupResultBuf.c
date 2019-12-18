#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tFilePage ;
typedef  size_t int32_t ;
struct TYPE_10__ {size_t nAlloc; TYPE_2__** result; int /*<<< orphan*/ * resultInfo; } ;
struct TYPE_9__ {size_t numOfOutputCols; TYPE_1__* pSelectExpr; } ;
struct TYPE_8__ {scalar_t__ numOfElems; } ;
struct TYPE_7__ {size_t interResBytes; } ;
typedef  int /*<<< orphan*/  SResultInfo ;
typedef  TYPE_3__ SQuery ;
typedef  TYPE_4__ SOutputRes ;

/* Variables and functions */
 size_t POINTER_BYTES ; 
 int /*<<< orphan*/ * calloc (size_t,int) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  setResultInfoBuf (int /*<<< orphan*/ *,size_t,int) ; 

void createGroupResultBuf(SQuery *pQuery, SOutputRes *pOneResult, bool isMetricQuery) {
  int32_t numOfOutput = pQuery->numOfOutputCols;

  pOneResult->resultInfo = calloc((size_t)numOfOutput, sizeof(SResultInfo));

  pOneResult->result = malloc(POINTER_BYTES * numOfOutput);
  for (int32_t i = 0; i < numOfOutput; ++i) {
    size_t       size = pQuery->pSelectExpr[i].interResBytes;
    SResultInfo *pResInfo = &pOneResult->resultInfo[i];

    pOneResult->result[i] = malloc(sizeof(tFilePage) + size * pOneResult->nAlloc);
    pOneResult->result[i]->numOfElems = 0;

    setResultInfoBuf(pResInfo, (int32_t)size, isMetricQuery);
  }
}