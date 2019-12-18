#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_24__ ;
typedef  struct TYPE_26__   TYPE_21__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_25__ {int numOfSids; size_t* starterPos; } ;
typedef  TYPE_1__ tSidSet ;
typedef  scalar_t__ int64_t ;
typedef  size_t int32_t ;
struct TYPE_35__ {scalar_t__ compInfoOffset; } ;
struct TYPE_34__ {TYPE_24__* pMeterQInfo; scalar_t__ offsetInHeaderFile; int /*<<< orphan*/ * pMeterObj; } ;
struct TYPE_33__ {scalar_t__ lastKeyOnFile; int sid; int /*<<< orphan*/  meterId; int /*<<< orphan*/  vnode; } ;
struct TYPE_32__ {scalar_t__ rawSKey; scalar_t__ rawEKey; int /*<<< orphan*/  pMeterObj; TYPE_5__** pMeterSidExtInfo; } ;
struct TYPE_31__ {int /*<<< orphan*/  sid; } ;
struct TYPE_30__ {TYPE_6__* pMeterQuerySupporter; int /*<<< orphan*/  query; } ;
struct TYPE_29__ {char* pHeaderFileData; scalar_t__ headFileSize; int /*<<< orphan*/  headerFilePath; } ;
struct TYPE_26__ {int maxSessions; } ;
struct TYPE_28__ {TYPE_21__ cfg; int /*<<< orphan*/  fileId; int /*<<< orphan*/  numOfFiles; } ;
struct TYPE_27__ {scalar_t__ lastKey; } ;
typedef  scalar_t__ TSKEY ;
typedef  int /*<<< orphan*/  TSCKSUM ;
typedef  TYPE_2__ SVnodeObj ;
typedef  TYPE_3__ SQueryFileInfo ;
typedef  int /*<<< orphan*/  SQuery ;
typedef  TYPE_4__ SQInfo ;
typedef  TYPE_5__ SMeterSidExtInfo ;
typedef  TYPE_6__ SMeterQuerySupportObj ;
typedef  TYPE_7__ SMeterObj ;
typedef  TYPE_8__ SMeterDataInfo ;
typedef  TYPE_9__ SCompHeader ;

/* Variables and functions */
 int POINTER_BYTES ; 
 scalar_t__ QUERY_IS_ASC_QUERY (int /*<<< orphan*/ *) ; 
 scalar_t__ TSDB_FILE_HEADER_LEN ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_24__* createMeterQueryInfo (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dError (char*,TYPE_4__*,int /*<<< orphan*/ ,...) ; 
 TYPE_7__* getMeterObj (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ getOldestKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_21__*) ; 
 TYPE_8__** malloc (int) ; 
 int /*<<< orphan*/  offsetComparator ; 
 int /*<<< orphan*/  qsort (TYPE_8__**,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setMeterDataInfo (TYPE_8__*,TYPE_7__*,size_t,size_t) ; 
 scalar_t__ validateHeaderOffsetSegment (TYPE_4__*,int /*<<< orphan*/ ,size_t,char*,size_t) ; 
 TYPE_2__* vnodeList ; 

SMeterDataInfo **vnodeFilterQualifiedMeters(SQInfo *pQInfo, int32_t vid, SQueryFileInfo *pQueryFileInfo,
                                            tSidSet *pSidSet, SMeterDataInfo *pMeterDataInfo, int32_t *numOfMeters) {
  SQuery *               pQuery = &pQInfo->query;
  SMeterQuerySupportObj *pSupporter = pQInfo->pMeterQuerySupporter;
  SMeterSidExtInfo **    pMeterSidExtInfo = pSupporter->pMeterSidExtInfo;

  SVnodeObj *pVnode = &vnodeList[vid];

  char *  pHeaderData = pQueryFileInfo->pHeaderFileData;
  int32_t tmsize = sizeof(SCompHeader) * (pVnode->cfg.maxSessions) + sizeof(TSCKSUM);

  // file is corrupted, abort query in current file
  if (validateHeaderOffsetSegment(pQInfo, pQueryFileInfo->headerFilePath, vid, pHeaderData, tmsize) < 0) {
    *numOfMeters = 0;
    return 0;
  }

  int64_t          oldestKey = getOldestKey(pVnode->numOfFiles, pVnode->fileId, &pVnode->cfg);
  SMeterDataInfo **pReqMeterDataInfo = malloc(POINTER_BYTES * pSidSet->numOfSids);

  int32_t groupId = 0;
  TSKEY   skey, ekey;

  for (int32_t i = 0; i < pSidSet->numOfSids; ++i) {  // load all meter meta info
    SMeterObj *pMeterObj = getMeterObj(pSupporter->pMeterObj, pMeterSidExtInfo[i]->sid);
    if (pMeterObj == NULL) {
      dError("QInfo:%p failed to find required sid:%d", pQInfo, pMeterSidExtInfo[i]->sid);
      continue;
    }

    if (i >= pSidSet->starterPos[groupId + 1]) {
      groupId += 1;
    }

    SMeterDataInfo *pOneMeterDataInfo = &pMeterDataInfo[i];
    if (pOneMeterDataInfo->pMeterObj == NULL) {
      setMeterDataInfo(pOneMeterDataInfo, pMeterObj, i, groupId);
    }

    /* restore possible exists new query range for this meter, which starts from cache */
    if (pOneMeterDataInfo->pMeterQInfo != NULL) {
      skey = pOneMeterDataInfo->pMeterQInfo->lastKey;
    } else {
      skey = pSupporter->rawSKey;
    }

    // query on disk data files, which actually starts from the lastkey
    ekey = pSupporter->rawEKey;

    if (QUERY_IS_ASC_QUERY(pQuery)) {
      assert(skey >= pSupporter->rawSKey);
      if (ekey < oldestKey || skey > pMeterObj->lastKeyOnFile) {
        continue;
      }
    } else {
      assert(skey <= pSupporter->rawSKey);
      if (skey < oldestKey || ekey > pMeterObj->lastKeyOnFile) {
        continue;
      }
    }

    int64_t headerOffset = TSDB_FILE_HEADER_LEN + sizeof(SCompHeader) * pMeterObj->sid;

    SCompHeader *compHeader = (SCompHeader *)(pHeaderData + headerOffset);

    if (compHeader->compInfoOffset == 0) {
      continue;
    }

    if (compHeader->compInfoOffset < sizeof(SCompHeader) * pVnode->cfg.maxSessions + TSDB_FILE_HEADER_LEN ||
        compHeader->compInfoOffset > pQueryFileInfo->headFileSize) {
      dError("QInfo:%p vid:%d sid:%d id:%s, compInfoOffset:%d is not valid", pQuery, pMeterObj->vnode, pMeterObj->sid,
             pMeterObj->meterId, compHeader->compInfoOffset);
      continue;
    }

    pOneMeterDataInfo->offsetInHeaderFile = (uint64_t)compHeader->compInfoOffset;

    if (pOneMeterDataInfo->pMeterQInfo == NULL) {
      pOneMeterDataInfo->pMeterQInfo = createMeterQueryInfo(pQuery, pSupporter->rawSKey, pSupporter->rawEKey);
    }

    pReqMeterDataInfo[*numOfMeters] = pOneMeterDataInfo;
    (*numOfMeters) += 1;
  }

  assert(*numOfMeters <= pSidSet->numOfSids);

  /* enable access sequentially */
  if (*numOfMeters > 1) {
    qsort(pReqMeterDataInfo, *numOfMeters, POINTER_BYTES, offsetComparator);
  }

  return pReqMeterDataInfo;
}