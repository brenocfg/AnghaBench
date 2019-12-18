#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {char* data; int /*<<< orphan*/  rowSize; scalar_t__ id; int /*<<< orphan*/  delimiter; } ;
struct TYPE_12__ {int /*<<< orphan*/  rowSize; scalar_t__ id; int /*<<< orphan*/  offset; void* row; } ;
struct TYPE_11__ {int maxRowSize; int /*<<< orphan*/  mutex; void* (* appTool ) (int /*<<< orphan*/ ,void*,char*,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  size; int /*<<< orphan*/  fd; scalar_t__ id; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  TSCKSUM ;
typedef  TYPE_1__ SSdbTable ;
typedef  TYPE_2__ SRowMeta ;
typedef  TYPE_3__ SRowHead ;

/* Variables and functions */
 int /*<<< orphan*/  SDB_DELIMITER ; 
 int /*<<< orphan*/  SDB_TYPE_AFTER_BATCH_UPDATE ; 
 int /*<<< orphan*/  SDB_TYPE_BATCH_UPDATE ; 
 int /*<<< orphan*/  SDB_TYPE_BEFORE_BATCH_UPDATE ; 
 int /*<<< orphan*/  SDB_TYPE_ENCODE ; 
 int /*<<< orphan*/  SDB_TYPE_UPDATE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdbAddIntoUpdateList (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  sdbError (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdbFinishCommit (TYPE_1__*) ; 
 scalar_t__ sdbForwardDbReqToPeer (TYPE_1__*,int /*<<< orphan*/ ,void*,int) ; 
 TYPE_2__* sdbGetRowMeta (void*,void*) ; 
 int /*<<< orphan*/  sdbTrace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdbVersion ; 
 void* stub1 (int /*<<< orphan*/ ,void*,char*,int,int /*<<< orphan*/ *) ; 
 void* stub2 (int /*<<< orphan*/ ,void*,char*,int,int /*<<< orphan*/ *) ; 
 void* stub3 (int /*<<< orphan*/ ,void*,char*,int,int /*<<< orphan*/ *) ; 
 void* stub4 (int /*<<< orphan*/ ,void*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taosCalcChecksumAppend (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  tfree (TYPE_3__*) ; 
 int /*<<< orphan*/  twrite (int /*<<< orphan*/ ,TYPE_3__*,scalar_t__) ; 

int sdbBatchUpdateRow(void *handle, void *row, int rowSize) {
  SSdbTable *pTable = (SSdbTable *)handle;
  SRowMeta * pMeta = NULL;
  int        total_size = 0;
  /* char        action = SDB_TYPE_BATCH_UPDATE; */

  if (pTable == NULL || row == NULL || rowSize <= 0) return -1;
  pMeta = sdbGetRowMeta(handle, row);
  if (pMeta == NULL) {
    sdbTrace("table: %s, record is not there, batch update failed", pTable->name);
    return -1;
  }

  void *pMetaRow = pMeta->row;
  assert(pMetaRow != NULL);

  total_size = sizeof(SRowHead) + pTable->maxRowSize + sizeof(TSCKSUM);
  SRowHead *rowHead = (SRowHead *)malloc(total_size);
  if (rowHead == NULL) {
    sdbError("failed to allocate row head memory, sdb: %s", pTable->name);
    return -1;
  }

  pthread_mutex_lock(&pTable->mutex);
  if (sdbForwardDbReqToPeer(pTable, SDB_TYPE_BATCH_UPDATE, row, rowSize) == 0) {
    /* // write action */
    /* write(pTable->fd, &action, sizeof(action)); */
    /* pTable->size += sizeof(action); */

    (*(pTable->appTool))(SDB_TYPE_BEFORE_BATCH_UPDATE, pMetaRow, NULL, 0, NULL);

    void *next_row = pMetaRow;
    while (next_row != NULL) {
      pTable->id++;
      sdbVersion++;

      void *last_row = next_row;
      next_row = (*(pTable->appTool))(SDB_TYPE_BATCH_UPDATE, last_row, (char *)row, rowSize, 0);
      memset(rowHead, 0, sizeof(SRowHead) + pTable->maxRowSize + sizeof(TSCKSUM));

      // update in current layer
      pMeta->id = pTable->id;
      pMeta->offset = pTable->size;

      // write to disk
      rowHead->delimiter = SDB_DELIMITER;
      rowHead->id = pMeta->id;
      (*(pTable->appTool))(SDB_TYPE_ENCODE, last_row, rowHead->data, pTable->maxRowSize, &(rowHead->rowSize));
      taosCalcChecksumAppend(0, (uint8_t *)rowHead, sizeof(SRowHead) + rowHead->rowSize + sizeof(TSCKSUM));
      pMeta->rowSize = rowHead->rowSize;
      lseek(pTable->fd, pTable->size, SEEK_SET);
      twrite(pTable->fd, rowHead, sizeof(SRowHead) + rowHead->rowSize + sizeof(TSCKSUM));
      pTable->size += (sizeof(SRowHead) + rowHead->rowSize + sizeof(TSCKSUM));

      sdbAddIntoUpdateList(pTable, SDB_TYPE_UPDATE, last_row);

      if (next_row != NULL) {
        pMeta = sdbGetRowMeta(handle, next_row);
      }
    }

    sdbFinishCommit(pTable);

    (*(pTable->appTool))(SDB_TYPE_AFTER_BATCH_UPDATE, pMetaRow, NULL, 0, NULL);
  }
  pthread_mutex_unlock(&pTable->mutex);

  tfree(rowHead);

  return 0;
}