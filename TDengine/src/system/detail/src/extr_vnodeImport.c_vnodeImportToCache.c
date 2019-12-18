#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int numOfPoints; char** offset; } ;
struct TYPE_16__ {int unCommittedBlocks; int currentSlot; int maxBlocks; TYPE_7__** cacheBlocks; } ;
struct TYPE_15__ {int commit; int pos; int slot; scalar_t__ importedRows; TYPE_4__* pObj; } ;
struct TYPE_14__ {size_t vnode; int pointsPerBlock; int bytesPerPoint; int freePoints; int numOfColumns; int /*<<< orphan*/  meterId; int /*<<< orphan*/  sid; TYPE_1__* schema; scalar_t__ pCache; } ;
struct TYPE_13__ {int cacheBlockSize; } ;
struct TYPE_12__ {scalar_t__ firstKey; int /*<<< orphan*/  vmutex; TYPE_3__ cfg; } ;
struct TYPE_11__ {int bytes; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_2__ SVnodeObj ;
typedef  TYPE_3__ SVnodeCfg ;
typedef  TYPE_4__ SMeterObj ;
typedef  TYPE_5__ SImportInfo ;
typedef  TYPE_6__ SCacheInfo ;
typedef  TYPE_7__ SCacheBlock ;

/* Variables and functions */
 int TSDB_CODE_ACTION_IN_PROGRESS ; 
 int TSDB_MAX_COLUMNS ; 
 int /*<<< orphan*/  atomic_fetch_sub_32 (int*,int) ; 
 int /*<<< orphan*/  dError (char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dTrace (char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int vnodeAllocateCacheBlock (TYPE_4__*) ; 
 TYPE_2__* vnodeList ; 

int vnodeImportToCache(SImportInfo *pImport, char *payload, int rows) {
  SMeterObj  *pObj = pImport->pObj;
  SVnodeObj  *pVnode = &vnodeList[pObj->vnode];
  SVnodeCfg  *pCfg = &pVnode->cfg;
  int         code = -1;
  SCacheInfo *pInfo = (SCacheInfo *)pObj->pCache;
  int         slot, pos, row, col, points, tpoints;

  char *data[TSDB_MAX_COLUMNS], *current[TSDB_MAX_COLUMNS];
  int   slots = pInfo->unCommittedBlocks + 1;
  int   trows = slots * pObj->pointsPerBlock + rows;  // max rows in buffer
  int   tsize = (trows / pObj->pointsPerBlock + 1) * pCfg->cacheBlockSize;
  TSKEY firstKey = *((TSKEY *)payload);
  TSKEY lastKey = *((TSKEY *)(payload + pObj->bytesPerPoint * (rows - 1)));

  if (pObj->freePoints < rows || pObj->freePoints < (pObj->pointsPerBlock << 1)) {
    dError("vid:%d sid:%d id:%s, import failed, cache is full, freePoints:%d", pObj->vnode, pObj->sid, pObj->meterId,
           pObj->freePoints);
    pImport->importedRows = 0;
    pImport->commit = 1;
    code = TSDB_CODE_ACTION_IN_PROGRESS;
    return code;
  }

  dTrace("vid:%d sid:%d id:%s, %d rows data will be imported to cache, firstKey:%ld lastKey:%ld",
      pObj->vnode, pObj->sid, pObj->meterId, rows, firstKey, lastKey);

  pthread_mutex_lock(&(pVnode->vmutex));
  if (firstKey < pVnode->firstKey) pVnode->firstKey = firstKey;
  pthread_mutex_unlock(&(pVnode->vmutex));

  char *buffer = malloc(tsize);  // buffer to hold unCommitted data plus import data
  data[0] = buffer;
  current[0] = data[0];
  for (col = 1; col < pObj->numOfColumns; ++col) {
    data[col] = data[col - 1] + trows * pObj->schema[col - 1].bytes;
    current[col] = data[col];
  }

  // write import data into buffer first
  for (row = 0; row < rows; ++row) {
    for (col = 0; col < pObj->numOfColumns; ++col) {
      memcpy(current[col], payload, pObj->schema[col].bytes);
      payload += pObj->schema[col].bytes;
      current[col] += pObj->schema[col].bytes;
    }
  }

  // copy the overwritten data into buffer
  tpoints = rows;
  pos = pImport->pos;
  slot = pImport->slot;
  while (1) {
    points = pInfo->cacheBlocks[slot]->numOfPoints - pos;
    for (col = 0; col < pObj->numOfColumns; ++col) {
      int size = points * pObj->schema[col].bytes;
      memcpy(current[col], pInfo->cacheBlocks[slot]->offset[col] + pos * pObj->schema[col].bytes, size);
      current[col] += size;
    }
    pos = 0;
    tpoints += points;

    if (slot == pInfo->currentSlot) break;
    slot = (slot + 1) % pInfo->maxBlocks;
  }

  for (col = 0; col < pObj->numOfColumns; ++col) current[col] = data[col];
  pos = pImport->pos;

  // write back to existing slots first
  slot = pImport->slot;
  while (1) {
    points = (tpoints > pObj->pointsPerBlock - pos) ? pObj->pointsPerBlock - pos : tpoints;
    SCacheBlock *pCacheBlock = pInfo->cacheBlocks[slot];
    for (col = 0; col < pObj->numOfColumns; ++col) {
      int size = points * pObj->schema[col].bytes;
      memcpy(pCacheBlock->offset[col] + pos * pObj->schema[col].bytes, current[col], size);
      current[col] += size;
    }
    pCacheBlock->numOfPoints = points + pos;
    pos = 0;
    tpoints -= points;

    if (slot == pInfo->currentSlot) break;
    slot = (slot + 1) % pInfo->maxBlocks;
  }

  // allocate new cache block if there are still data left
  while (tpoints > 0) {
    pImport->commit = vnodeAllocateCacheBlock(pObj);
    if (pImport->commit < 0) goto _exit;
    points = (tpoints > pObj->pointsPerBlock) ? pObj->pointsPerBlock : tpoints;
    SCacheBlock *pCacheBlock = pInfo->cacheBlocks[pInfo->currentSlot];
    for (col = 0; col < pObj->numOfColumns; ++col) {
      int size = points * pObj->schema[col].bytes;
      memcpy(pCacheBlock->offset[col] + pos * pObj->schema[col].bytes, current[col], size);
      current[col] += size;
    }
    tpoints -= points;
    pCacheBlock->numOfPoints = points;
  }

  code = 0;
  atomic_fetch_sub_32(&pObj->freePoints, rows);
  dTrace("vid:%d sid:%d id:%s, %d rows data are imported to cache", pObj->vnode, pObj->sid, pObj->meterId, rows);

_exit:
  free(buffer);
  return code;
}