#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_16__ {size_t numOfCols; } ;
struct TYPE_15__ {scalar_t__ colId; int /*<<< orphan*/  flag; } ;
struct TYPE_14__ {scalar_t__ colId; } ;
struct TYPE_13__ {size_t numOfOutputCols; TYPE_2__* pSelectExpr; } ;
struct TYPE_11__ {TYPE_5__ colInfo; } ;
struct TYPE_12__ {TYPE_1__ pBase; } ;
typedef  TYPE_3__ SQuery ;
typedef  TYPE_4__ SField ;
typedef  TYPE_5__ SColIndexEx ;
typedef  TYPE_6__ SBlockInfo ;

/* Variables and functions */
 scalar_t__ TSDB_COL_IS_TAG (int /*<<< orphan*/ ) ; 

__attribute__((used)) static SField *getFieldInfo(SQuery *pQuery, SBlockInfo *pBlockInfo, SField *pFields, int32_t column) {
  // no SField info exist, or column index larger than the output column, no result.
  if (pFields == NULL || column >= pQuery->numOfOutputCols) {
    return NULL;
  }

  SColIndexEx *pColIndexEx = &pQuery->pSelectExpr[column].pBase.colInfo;

  // for a tag column, no corresponding field info
  if (TSDB_COL_IS_TAG(pColIndexEx->flag)) {
    return NULL;
  }

  /*
   * Choose the right column field info by field id, since the file block may be out of date,
   * which means the newest table schema is not equalled to the schema of this block.
   */
  for (int32_t i = 0; i < pBlockInfo->numOfCols; ++i) {
    if (pColIndexEx->colId == pFields[i].colId) {
      return &pFields[i];
    }
  }

  return NULL;
}