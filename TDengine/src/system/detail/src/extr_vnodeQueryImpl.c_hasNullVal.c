#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_15__ {scalar_t__ numOfNullPoints; } ;
struct TYPE_14__ {TYPE_3__* pSelectExpr; } ;
struct TYPE_11__ {int /*<<< orphan*/  flag; } ;
struct TYPE_12__ {TYPE_1__ colInfo; } ;
struct TYPE_13__ {TYPE_2__ pBase; } ;
typedef  TYPE_4__ SQuery ;
typedef  TYPE_5__ SField ;
typedef  int /*<<< orphan*/  SBlockInfo ;

/* Variables and functions */
 scalar_t__ TSDB_COL_IS_TAG (int /*<<< orphan*/ ) ; 
 TYPE_5__* getFieldInfo (TYPE_4__*,int /*<<< orphan*/ *,TYPE_5__*,size_t) ; 

__attribute__((used)) static bool hasNullVal(SQuery *pQuery, int32_t col, SBlockInfo *pBlockInfo, SField *pFields, bool isDiskFileBlock) {
  bool ret = true;

  if (TSDB_COL_IS_TAG(pQuery->pSelectExpr[col].pBase.colInfo.flag)) {
    ret = false;
  } else if (isDiskFileBlock) {
    if (pFields == NULL) {
      ret = false;
    } else {
      SField *pField = getFieldInfo(pQuery, pBlockInfo, pFields, col);
      if (pField != NULL && pField->numOfNullPoints == 0) {
        ret = false;
      }
    }
  }

  return ret;
}