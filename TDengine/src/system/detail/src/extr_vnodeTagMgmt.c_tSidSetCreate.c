#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int numOfOrderedCols; int /*<<< orphan*/ * pData; } ;
struct TYPE_7__ {int numOfSids; int /*<<< orphan*/ * starterPos; TYPE_1__ orderIdx; int /*<<< orphan*/  pTagSchema; struct SMeterSidExtInfo** pSids; } ;
typedef  TYPE_2__ tSidSet ;
struct SMeterSidExtInfo {int dummy; } ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_8__ {scalar_t__ flag; int /*<<< orphan*/  colIdx; } ;
typedef  int /*<<< orphan*/  SSchema ;
typedef  TYPE_3__ SColIndexEx ;

/* Variables and functions */
 scalar_t__ TSDB_COL_TAG ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  tCreateTagSchema (int /*<<< orphan*/ *,int) ; 

tSidSet *tSidSetCreate(struct SMeterSidExtInfo **pMeterSidExtInfo, int32_t numOfMeters, SSchema *pSchema,
                       int32_t numOfTags, SColIndexEx *colList, int32_t numOfCols) {
  tSidSet *pSidSet = (tSidSet *)calloc(1, sizeof(tSidSet) + numOfCols * sizeof(int16_t));
  if (pSidSet == NULL) {
    return NULL;
  }

  pSidSet->numOfSids = numOfMeters;
  pSidSet->pSids = pMeterSidExtInfo;
  pSidSet->pTagSchema = tCreateTagSchema(pSchema, numOfTags);
  pSidSet->orderIdx.numOfOrderedCols = numOfCols;

  /*
   * in case of "group by tbname,normal_col", the normal_col is ignored
   */
  int32_t numOfTagCols = 0;
  for(int32_t i = 0; i < numOfCols; ++i) {
    if (colList[i].flag == TSDB_COL_TAG) {
      pSidSet->orderIdx.pData[numOfTagCols++] = colList[i].colIdx;
    }
  }

  pSidSet->orderIdx.numOfOrderedCols = numOfTagCols;

  pSidSet->starterPos = NULL;
  return pSidSet;
}