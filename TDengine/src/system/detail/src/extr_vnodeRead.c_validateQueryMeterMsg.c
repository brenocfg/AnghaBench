#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_4__ {scalar_t__ nAggTimeInterval; scalar_t__ numOfTagsCols; scalar_t__ numOfCols; scalar_t__ numOfSids; scalar_t__ numOfGroupCols; scalar_t__ numOfOutputCols; scalar_t__ tagLength; } ;
typedef  TYPE_1__ SQueryMeterMsg ;

/* Variables and functions */
 scalar_t__ TSDB_MAX_COLUMNS ; 
 scalar_t__ TSDB_MAX_TAGS ; 
 int /*<<< orphan*/  dError (char*,TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int32_t validateQueryMeterMsg(SQueryMeterMsg *pQueryMsg) {
  if (pQueryMsg->nAggTimeInterval < 0) {
    dError("qmsg:%p illegal value of aggTimeInterval %ld", pQueryMsg, pQueryMsg->nAggTimeInterval);
    return -1;
  }

  if (pQueryMsg->numOfTagsCols < 0 || pQueryMsg->numOfTagsCols > TSDB_MAX_TAGS + 1) {
    dError("qmsg:%p illegal value of numOfTagsCols %ld", pQueryMsg, pQueryMsg->numOfTagsCols);
    return -1;
  }

  if (pQueryMsg->numOfCols <= 0 || pQueryMsg->numOfCols > TSDB_MAX_COLUMNS) {
    dError("qmsg:%p illegal value of numOfCols %ld", pQueryMsg, pQueryMsg->numOfCols);
    return -1;
  }

  if (pQueryMsg->numOfSids <= 0) {
    dError("qmsg:%p illegal value of numOfSids %ld", pQueryMsg, pQueryMsg->numOfSids);
    return -1;
  }

  if (pQueryMsg->numOfGroupCols < 0) {
    dError("qmsg:%p illegal value of numOfGroupbyCols %ld", pQueryMsg, pQueryMsg->numOfGroupCols);
    return -1;
  }

  if (pQueryMsg->numOfOutputCols > TSDB_MAX_COLUMNS || pQueryMsg->numOfOutputCols <= 0) {
    dError("qmsg:%p illegal value of output columns %d", pQueryMsg, pQueryMsg->numOfOutputCols);
    return -1;
  }

  if (pQueryMsg->tagLength < 0) {
    dError("qmsg:%p illegal value of tag length %d", pQueryMsg, pQueryMsg->tagLength);
    return -1;
  }

  return 0;
}