#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_5__ {size_t numOfGroupCols; TYPE_1__* columnInfo; } ;
struct TYPE_4__ {scalar_t__ colId; scalar_t__ flag; } ;
typedef  TYPE_2__ SSqlGroupbyExpr ;

/* Variables and functions */
 scalar_t__ TSDB_COL_TAG ; 

__attribute__((used)) static bool tagColumnInGroupby(SSqlGroupbyExpr* pGroupbyExpr, int16_t columnId) {
  for (int32_t j = 0; j < pGroupbyExpr->numOfGroupCols; ++j) {
    if (columnId == pGroupbyExpr->columnInfo[j].colId && pGroupbyExpr->columnInfo[j].flag == TSDB_COL_TAG) {
      return true;
    }
  }

  return false;
}