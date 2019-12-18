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
struct TYPE_4__ {int num; } ;
typedef  TYPE_1__ tQueryResultset ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  SVnodeSidList ;
typedef  int /*<<< orphan*/  SMetricMeta ;
typedef  int /*<<< orphan*/  SMeterSidExtInfo ;

/* Variables and functions */
 int mgmtGetNumOfVnodesInResult (TYPE_1__*) ; 

__attribute__((used)) static int32_t mgmtGetMetricMetaMsgSize(tQueryResultset *pResult, int32_t tagLength, int32_t maxMetersPerQuery) {
  int32_t numOfVnodes = mgmtGetNumOfVnodesInResult(pResult);

  int32_t size = (sizeof(SMeterSidExtInfo) + tagLength) * pResult->num +
                 ((pResult->num / maxMetersPerQuery) + 1 + numOfVnodes) * sizeof(SVnodeSidList) + sizeof(SMetricMeta) +
                 1024;

  return size;
}