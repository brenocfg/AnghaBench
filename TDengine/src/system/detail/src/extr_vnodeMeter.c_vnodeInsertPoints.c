#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int notFreeSlots; } ;
struct TYPE_19__ {int vnode; short bytesPerPoint; int pointsPerBlock; short freePoints; int sversion; scalar_t__ state; scalar_t__ lastKey; int numOfColumns; int /*<<< orphan*/  meterId; int /*<<< orphan*/  sid; } ;
struct TYPE_18__ {char* payLoad; int /*<<< orphan*/  numOfRows; } ;
struct TYPE_14__ {int /*<<< orphan*/  totalStorage; int /*<<< orphan*/  pointsWritten; } ;
struct TYPE_15__ {int totalBlocks; } ;
struct TYPE_16__ {int blocksPerMeter; int replications; scalar_t__ daysPerFile; size_t precision; scalar_t__ commitLog; TYPE_2__ cacheNumOfBlocks; } ;
struct TYPE_17__ {scalar_t__ logFd; int maxFiles; scalar_t__ lastKey; scalar_t__ firstKey; TYPE_1__ vnodeStatistic; int /*<<< orphan*/  vmutex; int /*<<< orphan*/  version; TYPE_3__ cfg; int /*<<< orphan*/  lastKeyOnFile; scalar_t__ pCachePool; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_4__ SVnodeObj ;
typedef  TYPE_5__ SSubmitMsg ;
typedef  TYPE_6__ SMeterObj ;
typedef  TYPE_7__ SCachePool ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_ACTION_INSERT ; 
 int TSDB_CODE_ACTION_IN_PROGRESS ; 
 int TSDB_CODE_BATCH_SIZE_TOO_BIG ; 
 int TSDB_CODE_INVALID_COMMIT_LOG ; 
 int TSDB_CODE_NOT_ACTIVE_SESSION ; 
 int TSDB_CODE_SUCCESS ; 
 int TSDB_CODE_TIMESTAMP_OUT_OF_RANGE ; 
 int TSDB_CODE_WRONG_MSG_SIZE ; 
 char TSDB_DATA_SOURCE_LOG ; 
 char TSDB_DATA_SOURCE_SHELL ; 
 scalar_t__ TSDB_METER_STATE_DELETING ; 
 int /*<<< orphan*/  VALID_TIMESTAMP (scalar_t__,scalar_t__,size_t) ; 
 int /*<<< orphan*/  atomic_fetch_add_64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dError (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  dTrace (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,short,...) ; 
 int /*<<< orphan*/  dWarn (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,...) ; 
 short htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__* tsMsPerDay ; 
 int vnodeForwardToPeer (TYPE_6__*,char*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vnodeInsertPointToCache (TYPE_6__*,char*) ; 
 TYPE_4__* vnodeList ; 
 int /*<<< orphan*/  vnodeProcessCommitTimer (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnodeSendMeterCfgMsg (int,int /*<<< orphan*/ ) ; 
 int vnodeWriteToCommitLog (TYPE_6__*,int /*<<< orphan*/ ,char*,int,int) ; 

int vnodeInsertPoints(SMeterObj *pObj, char *cont, int contLen, char source, void *param, int sversion,
                      int *numOfInsertPoints, TSKEY now) {
  int         expectedLen, i;
  short       numOfPoints;
  SSubmitMsg *pSubmit = (SSubmitMsg *)cont;
  char *      pData;
  TSKEY       tsKey;
  int         points = 0;
  int         code = TSDB_CODE_SUCCESS;
  SVnodeObj * pVnode = vnodeList + pObj->vnode;

  numOfPoints = htons(pSubmit->numOfRows);
  expectedLen = numOfPoints * pObj->bytesPerPoint + sizeof(pSubmit->numOfRows);
  if (expectedLen != contLen) {
    dError("vid:%d sid:%d id:%s, invalid submit msg length:%d, expected:%d, bytesPerPoint: %d",
           pObj->vnode, pObj->sid, pObj->meterId, contLen, expectedLen, pObj->bytesPerPoint);
    code = TSDB_CODE_WRONG_MSG_SIZE;
    goto _over;
  }

  // to guarantee time stamp is the same for all vnodes
  pData = pSubmit->payLoad;
  tsKey = now;
  if (*((TSKEY *)pData) == 0) {
    for (i = 0; i < numOfPoints; ++i) {
      *((TSKEY *)pData) = tsKey++;
      pData += pObj->bytesPerPoint;
    }
  }

  if (numOfPoints >= (pVnode->cfg.blocksPerMeter - 2) * pObj->pointsPerBlock) {
    code = TSDB_CODE_BATCH_SIZE_TOO_BIG;
    dError("vid:%d sid:%d id:%s, batch size too big, it shall be smaller than:%d", pObj->vnode, pObj->sid,
           pObj->meterId, (pVnode->cfg.blocksPerMeter - 2) * pObj->pointsPerBlock);
    return code;
  }

  SCachePool *pPool = (SCachePool *)pVnode->pCachePool;
  if (pObj->freePoints < numOfPoints || pObj->freePoints < (pObj->pointsPerBlock << 1) ||
      pPool->notFreeSlots > pVnode->cfg.cacheNumOfBlocks.totalBlocks - 2) {
    code = TSDB_CODE_ACTION_IN_PROGRESS;
    dTrace("vid:%d sid:%d id:%s, cache is full, freePoints:%d, notFreeSlots:%d", pObj->vnode, pObj->sid, pObj->meterId,
           pObj->freePoints, pPool->notFreeSlots);
    vnodeProcessCommitTimer(pVnode, NULL);
    return TSDB_CODE_ACTION_IN_PROGRESS;
  }

  // FIXME: Here should be after the comparison of sversions.
  if (pVnode->cfg.commitLog && source != TSDB_DATA_SOURCE_LOG) {
    if (pVnode->logFd < 0) return TSDB_CODE_INVALID_COMMIT_LOG;
    code = vnodeWriteToCommitLog(pObj, TSDB_ACTION_INSERT, cont, contLen, sversion);
    if (code != 0) return code;
  }

  if (source == TSDB_DATA_SOURCE_SHELL && pVnode->cfg.replications > 1) {
    code = vnodeForwardToPeer(pObj, cont, contLen, TSDB_ACTION_INSERT, sversion);
    if (code != 0) return code;
  }

  if (pObj->sversion < sversion) {
    dTrace("vid:%d sid:%d id:%s, schema is changed, new:%d old:%d", pObj->vnode, pObj->sid, pObj->meterId, sversion,
           pObj->sversion);
    vnodeSendMeterCfgMsg(pObj->vnode, pObj->sid);
    code = TSDB_CODE_ACTION_IN_PROGRESS;
    return code;
  }

  pData = pSubmit->payLoad;
  code = 0;

  TSKEY firstKey = *((TSKEY *)pData);
  TSKEY lastKey = *((TSKEY *)(pData + pObj->bytesPerPoint * (numOfPoints - 1)));
  int cfid = now/pVnode->cfg.daysPerFile/tsMsPerDay[pVnode->cfg.precision];
  TSKEY minAllowedKey = (cfid - pVnode->maxFiles + 1)*pVnode->cfg.daysPerFile*tsMsPerDay[pVnode->cfg.precision];
  TSKEY maxAllowedKey = (cfid + 2)*pVnode->cfg.daysPerFile*tsMsPerDay[pVnode->cfg.precision] - 2;
  if (firstKey < minAllowedKey || firstKey > maxAllowedKey || lastKey < minAllowedKey || lastKey > maxAllowedKey) {
    dError("vid:%d sid:%d id:%s, vnode lastKeyOnFile:%lld, data is out of range, numOfPoints:%d firstKey:%lld lastKey:%lld minAllowedKey:%lld maxAllowedKey:%lld",
            pObj->vnode, pObj->sid, pObj->meterId, pVnode->lastKeyOnFile, numOfPoints,firstKey, lastKey, minAllowedKey, maxAllowedKey);
    return TSDB_CODE_TIMESTAMP_OUT_OF_RANGE;
  }

  for (i = 0; i < numOfPoints; ++i) {
    // meter will be dropped, abort current insertion
    if (pObj->state >= TSDB_METER_STATE_DELETING) {
      dWarn("vid:%d sid:%d id:%s, meter is dropped, abort insert, state:%d", pObj->vnode, pObj->sid, pObj->meterId,
            pObj->state);

      code = TSDB_CODE_NOT_ACTIVE_SESSION;
      break;
    }

    if (*((TSKEY *)pData) <= pObj->lastKey) {
      dWarn("vid:%d sid:%d id:%s, received key:%ld not larger than lastKey:%ld", pObj->vnode, pObj->sid, pObj->meterId,
            *((TSKEY *)pData), pObj->lastKey);
      pData += pObj->bytesPerPoint;
      continue;
    }

    if (!VALID_TIMESTAMP(*((TSKEY *)pData), tsKey, pVnode->cfg.precision)) {
      code = TSDB_CODE_TIMESTAMP_OUT_OF_RANGE;
      break;
    }

    if (vnodeInsertPointToCache(pObj, pData) < 0) {
      code = TSDB_CODE_ACTION_IN_PROGRESS;
      break;
    }

    pObj->lastKey = *((TSKEY *)pData);
    pData += pObj->bytesPerPoint;
    points++;
  }
  atomic_fetch_add_64(&(pVnode->vnodeStatistic.pointsWritten), points * (pObj->numOfColumns - 1));
  atomic_fetch_add_64(&(pVnode->vnodeStatistic.totalStorage), points * pObj->bytesPerPoint);

  pthread_mutex_lock(&(pVnode->vmutex));

  if (pObj->lastKey > pVnode->lastKey) pVnode->lastKey = pObj->lastKey;

  if (firstKey < pVnode->firstKey) pVnode->firstKey = firstKey;

  pVnode->version++;

  pthread_mutex_unlock(&(pVnode->vmutex));

_over:
  dTrace("vid:%d sid:%d id:%s, %d out of %d points are inserted, lastKey:%ld source:%d, vnode total storage: %ld",
         pObj->vnode, pObj->sid, pObj->meterId, points, numOfPoints, pObj->lastKey, source,
         pVnode->vnodeStatistic.totalStorage);

  *numOfInsertPoints = points;
  return code;
}