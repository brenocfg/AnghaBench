#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  double int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_14__ {TYPE_2__* pAcct; } ;
struct TYPE_9__ {double totalBlocks; } ;
struct TYPE_11__ {int daysToKeep1; int daysToKeep2; int daysToKeep; int maxSessions; double rowsInFileBlock; double cacheBlockSize; double commitTime; scalar_t__ precision; int /*<<< orphan*/  compression; int /*<<< orphan*/  commitLog; int /*<<< orphan*/  blocksPerMeter; TYPE_1__ cacheNumOfBlocks; int /*<<< orphan*/  daysPerFile; int /*<<< orphan*/  replications; } ;
struct TYPE_13__ {double numOfTables; double numOfVgroups; scalar_t__ dropStatus; TYPE_3__ cfg; int /*<<< orphan*/  createdTime; int /*<<< orphan*/  name; scalar_t__ next; } ;
struct TYPE_12__ {int* offset; int* bytes; int numOfReads; void* pNode; } ;
struct TYPE_10__ {int /*<<< orphan*/  user; } ;
typedef  TYPE_4__ SShowObj ;
typedef  TYPE_5__ SDbObj ;
typedef  TYPE_6__ SConnObj ;

/* Variables and functions */
 scalar_t__ TSDB_DB_STATUS_READY ; 
 char* TSDB_TIME_PRECISION_MICRO_STR ; 
 scalar_t__ TSDB_TIME_PRECISION_MILLI ; 
 char* TSDB_TIME_PRECISION_MILLI_STR ; 
 char* mgmtGetDbStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int mgmtRetrieveDbs(SShowObj *pShow, char *data, int rows, SConnObj *pConn) {
  int     numOfRows = 0;
  SDbObj *pDb = NULL;
  char *  pWrite;
  int     cols = 0;

  while (numOfRows < rows) {
    pDb = (SDbObj *)pShow->pNode;
    if (pDb == NULL) break;
    pShow->pNode = (void *)pDb->next;

    cols = 0;

    pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
    strcpy(pWrite, mgmtGetDbStr(pDb->name));
    cols++;

    pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
    *(int64_t *)pWrite = pDb->createdTime;
    cols++;

    pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
    *(int32_t *)pWrite = pDb->numOfTables;
    cols++;

#ifndef __CLOUD_VERSION__
    if (strcmp(pConn->pAcct->user, "root") == 0) {
#endif
      pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
      *(int32_t *)pWrite = pDb->numOfVgroups;
      cols++;
#ifndef __CLOUD_VERSION__
    }
#endif

#ifndef __CLOUD_VERSION__
    if (strcmp(pConn->pAcct->user, "root") == 0) {
#endif
      pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
      *(int16_t *)pWrite = pDb->cfg.replications;
      cols++;

      pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
      *(int16_t *)pWrite = pDb->cfg.daysPerFile;
      cols++;
#ifndef __CLOUD_VERSION__
    }
#endif

    pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
    sprintf(pWrite, "%d,%d,%d", pDb->cfg.daysToKeep1, pDb->cfg.daysToKeep2, pDb->cfg.daysToKeep);
    cols++;

#ifndef __CLOUD_VERSION__
    if (strcmp(pConn->pAcct->user, "root") == 0) {
#endif
      pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
      *(int32_t *)pWrite = pDb->cfg.maxSessions - 1;  // table num can be created should minus 1
      cols++;

      pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
      *(int32_t *)pWrite = pDb->cfg.rowsInFileBlock;
      cols++;

      pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
      *(int32_t *)pWrite = pDb->cfg.cacheBlockSize;
      cols++;

      pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
#ifdef _TD_ARM_32_
      *(int32_t *)pWrite = (pDb->cfg.cacheNumOfBlocks.totalBlocks * 1.0 / (pDb->cfg.maxSessions - 1));
#else
      *(float *)pWrite = (pDb->cfg.cacheNumOfBlocks.totalBlocks * 1.0 / (pDb->cfg.maxSessions - 1));
#endif
      cols++;

      pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
      *(int16_t *)pWrite = pDb->cfg.blocksPerMeter;
      cols++;

      pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
      *(int32_t *)pWrite = pDb->cfg.commitTime;
      cols++;

      pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
      *(int8_t *)pWrite = pDb->cfg.commitLog;
      cols++;

      pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
      *(int8_t *)pWrite = pDb->cfg.compression;
      cols++;
#ifndef __CLOUD_VERSION__
    }
#endif

    pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
    char *prec = (pDb->cfg.precision == TSDB_TIME_PRECISION_MILLI) ? TSDB_TIME_PRECISION_MILLI_STR
                                                                   : TSDB_TIME_PRECISION_MICRO_STR;
    strcpy(pWrite, prec);
    cols++;

    pWrite = data + pShow->offset[cols] * rows + pShow->bytes[cols] * numOfRows;
    strcpy(pWrite, pDb->dropStatus != TSDB_DB_STATUS_READY ? "dropping" : "ready");
    cols++;

    numOfRows++;
  }

  pShow->numOfReads += numOfRows;
  return numOfRows;
}