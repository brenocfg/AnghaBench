#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_9__ ;
typedef  struct TYPE_41__   TYPE_8__ ;
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_17__ ;
typedef  struct TYPE_32__   TYPE_16__ ;
typedef  struct TYPE_31__   TYPE_15__ ;
typedef  struct TYPE_30__   TYPE_14__ ;
typedef  struct TYPE_29__   TYPE_13__ ;
typedef  struct TYPE_28__   TYPE_12__ ;
typedef  struct TYPE_27__   TYPE_11__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  size_t int32_t ;
typedef  int int16_t ;
struct TYPE_26__ {size_t tableIndex; int numOfGroupCols; int orderIndex; int orderType; TYPE_17__* columnInfo; } ;
struct TYPE_40__ {size_t n; int /*<<< orphan*/  z; } ;
struct TYPE_39__ {scalar_t__ uid; TYPE_7__ cond; } ;
struct TYPE_35__ {int tagCol; int /*<<< orphan*/  meterId; } ;
struct TYPE_34__ {int tagCol; int /*<<< orphan*/  meterId; } ;
struct TYPE_36__ {TYPE_2__ right; TYPE_1__ left; } ;
struct TYPE_41__ {scalar_t__ numOfTagCond; int relType; TYPE_6__ tbnameCond; TYPE_3__ joinInfo; } ;
struct TYPE_27__ {char* payload; size_t numOfTables; int payloadLen; int /*<<< orphan*/  msgType; TYPE_10__ groupbyExpr; TYPE_8__ tagCond; } ;
struct TYPE_42__ {TYPE_11__ cmd; } ;
struct TYPE_38__ {int n; int /*<<< orphan*/  z; } ;
struct TYPE_37__ {scalar_t__ uid; } ;
struct TYPE_33__ {int colId; scalar_t__ flag; scalar_t__ colIdx; } ;
struct TYPE_32__ {TYPE_5__ cond; } ;
struct TYPE_31__ {size_t numOfTags; int* tagColumnIndex; int /*<<< orphan*/  name; TYPE_4__* pMeterMeta; } ;
struct TYPE_30__ {void* elemLen; void* numOfTags; int /*<<< orphan*/  meterId; void* groupbyTagColumnList; void* orderType; void* orderIndex; void** tagCols; void* numOfGroupCols; void* tableCondLen; void* tableCond; void* rel; void* cond; void* condLen; } ;
struct TYPE_29__ {void** metaElem; void* joinCondLen; void* join; void* numOfMeters; } ;
struct TYPE_28__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_8__ STagCond ;
typedef  TYPE_9__ SSqlObj ;
typedef  TYPE_10__ SSqlGroupbyExpr ;
typedef  TYPE_11__ SSqlCmd ;
typedef  TYPE_12__ SMgmtHead ;
typedef  TYPE_13__ SMetricMetaMsg ;
typedef  TYPE_14__ SMetricMetaElemMsg ;
typedef  TYPE_15__ SMeterMetaInfo ;
typedef  TYPE_16__ SCond ;
typedef  TYPE_17__ SColIndexEx ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int TSDB_METER_ID_LEN ; 
 int /*<<< orphan*/  TSDB_MSG_TYPE_METRIC_META ; 
 size_t TSDB_NCHAR_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 void* htonl (size_t) ; 
 void* htons (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 size_t minMsgSize () ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int taosMbsToUcs4 (int /*<<< orphan*/ ,int,char*,size_t) ; 
 TYPE_16__* tsGetMetricQueryCondPos (TYPE_8__*,scalar_t__) ; 
 int tsRpcHeadSize ; 
 scalar_t__ tscAllocPayload (TYPE_11__*,size_t) ; 
 int /*<<< orphan*/  tscError (char*,TYPE_9__*,...) ; 
 size_t tscEstimateMetricMetaMsgSize (TYPE_11__*) ; 
 int /*<<< orphan*/  tscGetDBInfoFromMeterId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_15__* tscGetMeterMetaInfo (TYPE_11__*,size_t) ; 

int tscBuildMetricMetaMsg(SSqlObj *pSql) {
  SMetricMetaMsg *pMetaMsg;
  char *          pMsg, *pStart;
  int             msgLen = 0;
  int             tableIndex = 0;

  SSqlCmd * pCmd = &pSql->cmd;
  STagCond *pTagCond = &pCmd->tagCond;

  SMeterMetaInfo *pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, tableIndex);

  int32_t size = tscEstimateMetricMetaMsgSize(pCmd);
  if (TSDB_CODE_SUCCESS != tscAllocPayload(pCmd, size)) {
    tscError("%p failed to malloc for metric meter msg", pSql);
    return -1;
  }

  pStart = pCmd->payload + tsRpcHeadSize;
  pMsg = pStart;

  SMgmtHead *pMgmt = (SMgmtHead *)pMsg;
  tscGetDBInfoFromMeterId(pMeterMetaInfo->name, pMgmt->db);

  pMsg += sizeof(SMgmtHead);

  pMetaMsg = (SMetricMetaMsg *)pMsg;
  pMetaMsg->numOfMeters = htonl(pCmd->numOfTables);

  pMsg += sizeof(SMetricMetaMsg);

  int32_t offset = pMsg - (char *)pMetaMsg;
  pMetaMsg->join = htonl(offset);

  // todo refactor
  pMetaMsg->joinCondLen = htonl((TSDB_METER_ID_LEN + sizeof(int16_t)) * 2);

  memcpy(pMsg, pTagCond->joinInfo.left.meterId, TSDB_METER_ID_LEN);
  pMsg += TSDB_METER_ID_LEN;

  *(int16_t *)pMsg = pTagCond->joinInfo.left.tagCol;
  pMsg += sizeof(int16_t);

  memcpy(pMsg, pTagCond->joinInfo.right.meterId, TSDB_METER_ID_LEN);
  pMsg += TSDB_METER_ID_LEN;

  *(int16_t *)pMsg = pTagCond->joinInfo.right.tagCol;
  pMsg += sizeof(int16_t);

  for (int32_t i = 0; i < pCmd->numOfTables; ++i) {
    pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, i);
    uint64_t uid = pMeterMetaInfo->pMeterMeta->uid;

    offset = pMsg - (char *)pMetaMsg;
    pMetaMsg->metaElem[i] = htonl(offset);

    SMetricMetaElemMsg *pElem = (SMetricMetaElemMsg *)pMsg;
    pMsg += sizeof(SMetricMetaElemMsg);

    // convert to unicode before sending to mnode for metric query
    int32_t condLen = 0;
    if (pTagCond->numOfTagCond > 0) {
      SCond *pCond = tsGetMetricQueryCondPos(pTagCond, uid);
      if (pCond != NULL) {
        condLen = pCond->cond.n + 1;
        bool ret = taosMbsToUcs4(pCond->cond.z, pCond->cond.n, pMsg, pCond->cond.n * TSDB_NCHAR_SIZE);
        if (!ret) {
          tscError("%p mbs to ucs4 failed:%s", pSql, tsGetMetricQueryCondPos(pTagCond, uid));
          return 0;
        }
      }
    }

    pElem->condLen = htonl(condLen);

    offset = pMsg - (char *)pMetaMsg;
    pElem->cond = htonl(offset);
    pMsg += condLen * TSDB_NCHAR_SIZE;

    pElem->rel = htons(pTagCond->relType);
    if (pTagCond->tbnameCond.uid == uid) {
      offset = pMsg - (char *)pMetaMsg;

      pElem->tableCond = htonl(offset);
      pElem->tableCondLen = htonl(pTagCond->tbnameCond.cond.n);

      memcpy(pMsg, pTagCond->tbnameCond.cond.z, pTagCond->tbnameCond.cond.n);
      pMsg += pTagCond->tbnameCond.cond.n;
    }

    SSqlGroupbyExpr *pGroupby = &pCmd->groupbyExpr;

    if (pGroupby->tableIndex != i) {
      pElem->orderType = 0;
      pElem->orderIndex = 0;
      pElem->numOfGroupCols = 0;
    } else {
      pElem->numOfGroupCols = htons(pGroupby->numOfGroupCols);
      for (int32_t j = 0; j < pMeterMetaInfo->numOfTags; ++j) {
        pElem->tagCols[j] = htons(pMeterMetaInfo->tagColumnIndex[j]);
      }

      if (pGroupby->numOfGroupCols != 0) {
        pElem->orderIndex = htons(pGroupby->orderIndex);
        pElem->orderType = htons(pGroupby->orderType);
        offset = pMsg - (char *)pMetaMsg;

        pElem->groupbyTagColumnList = htonl(offset);
        for (int32_t j = 0; j < pCmd->groupbyExpr.numOfGroupCols; ++j) {
          SColIndexEx *pCol = &pCmd->groupbyExpr.columnInfo[j];

          *((int16_t *)pMsg) = pCol->colId;
          pMsg += sizeof(pCol->colId);

          *((int16_t *)pMsg) += pCol->colIdx;
          pMsg += sizeof(pCol->colIdx);

          *((int16_t *)pMsg) += pCol->flag;
          pMsg += sizeof(pCol->flag);
        }
      }
    }

    strcpy(pElem->meterId, pMeterMetaInfo->name);
    pElem->numOfTags = htons(pMeterMetaInfo->numOfTags);

    int16_t len = pMsg - (char *)pElem;
    pElem->elemLen = htons(len);  // redundant data for integrate check
  }

  msgLen = pMsg - pStart;
  pCmd->payloadLen = msgLen;
  pCmd->msgType = TSDB_MSG_TYPE_METRIC_META;
  assert(msgLen + minMsgSize() <= size);
  return msgLen;
}