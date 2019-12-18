#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_10__ {size_t n; } ;
struct TYPE_11__ {TYPE_3__ cond; } ;
struct TYPE_12__ {size_t numOfTagCond; TYPE_4__ tbnameCond; TYPE_2__* cond; } ;
struct TYPE_13__ {int numOfTables; TYPE_5__ tagCond; } ;
struct TYPE_8__ {scalar_t__ n; } ;
struct TYPE_9__ {TYPE_1__ cond; } ;
typedef  TYPE_6__ SSqlCmd ;
typedef  int /*<<< orphan*/  SMgmtHead ;
typedef  int /*<<< orphan*/  SMetricMetaMsg ;
typedef  int /*<<< orphan*/  SMetricMetaElemMsg ;

/* Variables and functions */
 size_t MAX (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSDB_DEFAULT_PAYLOAD_SIZE ; 
 int TSDB_MAX_TAGS ; 
 int TSDB_METER_ID_LEN ; 
 size_t TSDB_NCHAR_SIZE ; 
 size_t minMsgSize () ; 

__attribute__((used)) static int32_t tscEstimateMetricMetaMsgSize(SSqlCmd *pCmd) {
  const int32_t defaultSize =
      minMsgSize() + sizeof(SMetricMetaMsg) + sizeof(SMgmtHead) + sizeof(int16_t) * TSDB_MAX_TAGS;

  int32_t n = 0;
  for (int32_t i = 0; i < pCmd->tagCond.numOfTagCond; ++i) {
    n += pCmd->tagCond.cond[i].cond.n;
  }

  int32_t tagLen = n * TSDB_NCHAR_SIZE + pCmd->tagCond.tbnameCond.cond.n * TSDB_NCHAR_SIZE;
  int32_t joinCondLen = (TSDB_METER_ID_LEN + sizeof(int16_t)) * 2;
  int32_t elemSize = sizeof(SMetricMetaElemMsg) * pCmd->numOfTables;

  int32_t len = tagLen + joinCondLen + elemSize + defaultSize;

  return MAX(len, TSDB_DEFAULT_PAYLOAD_SIZE);
}