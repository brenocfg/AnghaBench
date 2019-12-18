#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_10__ {int nStatus; } ;
struct TYPE_9__ {scalar_t__ functionId; } ;
struct TYPE_7__ {scalar_t__ numOfOutputCols; } ;
struct TYPE_8__ {TYPE_1__ fieldsInfo; } ;
typedef  TYPE_2__ SSqlCmd ;

/* Variables and functions */
 int TSDB_FUNCSTATE_SELECTIVITY ; 
 scalar_t__ TSDB_FUNC_TAG_DUMMY ; 
 TYPE_6__* aAggs ; 
 TYPE_3__* tscSqlExprGet (TYPE_2__*,scalar_t__) ; 

bool tscIsSelectivityWithTagQuery(SSqlCmd* pCmd) {
  bool    hasTags = false;
  int32_t numOfSelectivity = 0;

  for (int32_t i = 0; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
    int32_t functId = tscSqlExprGet(pCmd, i)->functionId;
    if (functId == TSDB_FUNC_TAG_DUMMY) {
      hasTags = true;
      continue;
    }

    if ((aAggs[functId].nStatus & TSDB_FUNCSTATE_SELECTIVITY) != 0) {
      numOfSelectivity++;
    }
  }

  if (numOfSelectivity > 0 && hasTags) {
    return true;
  }

  return false;
}