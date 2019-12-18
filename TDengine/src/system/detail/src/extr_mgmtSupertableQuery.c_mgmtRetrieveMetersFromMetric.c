#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSkipListNode ;
struct TYPE_19__ {scalar_t__ num; int /*<<< orphan*/  pRes; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ tQueryResultset ;
typedef  size_t int32_t ;
struct TYPE_23__ {scalar_t__ nSize; } ;
struct TYPE_22__ {int cond; size_t condLen; int tableCond; int tableCondLen; int /*<<< orphan*/  rel; int /*<<< orphan*/  meterId; } ;
struct TYPE_21__ {int* metaElem; } ;
struct TYPE_20__ {scalar_t__ numOfMeters; int /*<<< orphan*/  meterId; TYPE_6__* pSkipList; } ;
typedef  TYPE_2__ STabObj ;
typedef  TYPE_3__ SMetricMetaMsg ;
typedef  TYPE_4__ SMetricMetaElemMsg ;

/* Variables and functions */
 int TSDB_CODE_SUCCESS ; 
 size_t TSDB_NCHAR_SIZE ; 
 int /*<<< orphan*/  TSDB_RELATION_AND ; 
 int /*<<< orphan*/  TSDB_RELATION_OR ; 
 int /*<<< orphan*/  assert (int) ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  mTrace (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mgmtFilterByTableNameCond (TYPE_1__*,char*,int,TYPE_2__*) ; 
 size_t mgmtFilterMeterByIndex (TYPE_2__*,TYPE_1__*,char*,size_t) ; 
 TYPE_2__* mgmtGetMeter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queryResultIntersect (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  queryResultUnion (TYPE_1__*,TYPE_1__*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  tQueryResultClean (TYPE_1__*) ; 
 scalar_t__ tSkipListIterateList (TYPE_6__*,int /*<<< orphan*/ ***,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tansformQueryResult (TYPE_1__*) ; 
 int /*<<< orphan*/  taosUcs4ToMbs (char*,size_t,char*) ; 
 int /*<<< orphan*/  tfree (char*) ; 

int mgmtRetrieveMetersFromMetric(SMetricMetaMsg* pMsg, int32_t tableIndex, tQueryResultset* pRes) {
  SMetricMetaElemMsg* pElem = (SMetricMetaElemMsg*)((char*)pMsg + pMsg->metaElem[tableIndex]);
  STabObj*            pMetric = mgmtGetMeter(pElem->meterId);
  char*               pCond = NULL;
  char*               tmpTableNameCond = NULL;

  // no table created in accordance with this metric.
  if (pMetric->pSkipList == NULL || pMetric->pSkipList->nSize == 0) {
    assert(pMetric->numOfMeters == 0);
    return TSDB_CODE_SUCCESS;
  }

  char*   pQueryCond = (char*)pMsg + pElem->cond;
  int32_t condLen = pElem->condLen;

  // transfer the unicode string to mbs binary expression
  if (condLen > 0) {
    pCond = calloc(1, (condLen + 1) * TSDB_NCHAR_SIZE);

    taosUcs4ToMbs(pQueryCond, condLen * TSDB_NCHAR_SIZE, pCond);
    condLen = strlen(pCond) + 1;
    mTrace("metric:%s len:%d, metric query condition:%s", pMetric->meterId, condLen, pCond);
  }

  char* tablenameCond = (char*)pMsg + pElem->tableCond;

  if (pElem->tableCondLen > 0) {
    tmpTableNameCond = calloc(1, pElem->tableCondLen + 1);
    strncpy(tmpTableNameCond, tablenameCond, pElem->tableCondLen);

    mTrace("metric:%s rel:%d, len:%d, table name cond:%s", pMetric->meterId, pElem->rel, pElem->tableCondLen,
           tmpTableNameCond);
  }

  if (pElem->tableCondLen > 0 || condLen > 0) {
    mgmtFilterByTableNameCond(pRes, tmpTableNameCond, pElem->tableCondLen, pMetric);

    bool noNextCal = (pRes->num == 0 && pElem->rel == TSDB_RELATION_AND);  // no need to calculate next result

    if (!noNextCal && condLen > 0) {
      tQueryResultset filterRes = {0};

      int32_t ret = mgmtFilterMeterByIndex(pMetric, &filterRes, pCond, condLen);
      if (ret != TSDB_CODE_SUCCESS) {
        tfree(pCond);
        tfree(tmpTableNameCond);

        return ret;
      }

      // union or intersect of two results
      assert(pElem->rel == TSDB_RELATION_AND || pElem->rel == TSDB_RELATION_OR);

      if (pElem->rel == TSDB_RELATION_AND) {
        if (filterRes.num == 0 || pRes->num == 0) {  // intersect two sets
          tQueryResultClean(pRes);
        } else {
          queryResultIntersect(pRes, &filterRes);
        }
      } else {  // union two sets
        queryResultUnion(pRes, &filterRes);
      }

      tQueryResultClean(&filterRes);
    }
  } else {
    mTrace("metric:%s retrieve all meter, no query condition", pMetric->meterId);
    pRes->num = tSkipListIterateList(pMetric->pSkipList, (tSkipListNode***)&pRes->pRes, NULL, NULL);
    tansformQueryResult(pRes);
  }

  tfree(pCond);
  tfree(tmpTableNameCond);

  mTrace("metric:%s numOfRes:%d", pMetric->meterId, pRes->num);
  return TSDB_CODE_SUCCESS;
}