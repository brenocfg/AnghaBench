#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_4__ {scalar_t__ fraction; int totalBlocks; } ;
struct TYPE_5__ {scalar_t__ maxSessions; scalar_t__ cacheBlockSize; scalar_t__ daysPerFile; scalar_t__ daysToKeep; scalar_t__ daysToKeep1; scalar_t__ daysToKeep2; scalar_t__ commitTime; scalar_t__ compression; int commitLog; int replications; scalar_t__ rowsInFileBlock; scalar_t__ precision; int blocksPerMeter; TYPE_1__ cacheNumOfBlocks; } ;
typedef  TYPE_2__ SCreateDbMsg ;

/* Variables and functions */
 int TSDB_CODE_INVALID_OPTION ; 
 int TSDB_CODE_SUCCESS ; 
 scalar_t__ TSDB_FILE_MAX_PARTITION_RANGE ; 
 scalar_t__ TSDB_FILE_MIN_PARTITION_RANGE ; 
 scalar_t__ TSDB_MAX_AVG_BLOCKS ; 
 int TSDB_MAX_CACHE_BLOCKS ; 
 scalar_t__ TSDB_MAX_CACHE_BLOCK_SIZE ; 
 scalar_t__ TSDB_MAX_COMMIT_TIME_INTERVAL ; 
 scalar_t__ TSDB_MAX_COMPRESSION_LEVEL ; 
 scalar_t__ TSDB_MAX_ROWS_IN_FILEBLOCK ; 
 scalar_t__ TSDB_MAX_TABLES_PER_VNODE ; 
 scalar_t__ TSDB_MIN_CACHE_BLOCK_SIZE ; 
 scalar_t__ TSDB_MIN_COMMIT_TIME_INTERVAL ; 
 scalar_t__ TSDB_MIN_ROWS_IN_FILEBLOCK ; 
 scalar_t__ TSDB_MIN_TABLES_PER_VNODE ; 
 int TSDB_REPLICA_MAX_NUM ; 
 int TSDB_REPLICA_MIN_NUM ; 
 scalar_t__ TSDB_TIME_PRECISION_MICRO ; 
 scalar_t__ TSDB_TIME_PRECISION_MILLI ; 
 int TSDB_VNODES_SUPPORT ; 
 int /*<<< orphan*/  mTrace (char*,scalar_t__,...) ; 
 scalar_t__ tsAverageCacheBlocks ; 
 scalar_t__ tsCacheBlockSize ; 
 int tsCommitLog ; 
 scalar_t__ tsCommitTime ; 
 scalar_t__ tsCompression ; 
 scalar_t__ tsDaysPerFile ; 
 scalar_t__ tsDaysToKeep ; 
 int tsReplications ; 
 scalar_t__ tsRowsInFileBlock ; 
 scalar_t__ tsSessionsPerVnode ; 

int mgmtCheckDbParams(SCreateDbMsg *pCreate) {
  // assign default parameters
  if (pCreate->maxSessions < 0) pCreate->maxSessions = tsSessionsPerVnode;      //
  if (pCreate->cacheBlockSize < 0) pCreate->cacheBlockSize = tsCacheBlockSize;  //
  if (pCreate->daysPerFile < 0) pCreate->daysPerFile = tsDaysPerFile;           //
  if (pCreate->daysToKeep < 0) pCreate->daysToKeep = tsDaysToKeep;              //
  if (pCreate->daysToKeep1 < 0) pCreate->daysToKeep1 = pCreate->daysToKeep;     //
  if (pCreate->daysToKeep2 < 0) pCreate->daysToKeep2 = pCreate->daysToKeep;     //
  if (pCreate->commitTime < 0) pCreate->commitTime = tsCommitTime;              //
  if (pCreate->compression < 0) pCreate->compression = tsCompression;           //
  if (pCreate->commitLog < 0) pCreate->commitLog = tsCommitLog;
  if (pCreate->replications < 0) pCreate->replications = tsReplications;                                  //
  if (pCreate->rowsInFileBlock < 0) pCreate->rowsInFileBlock = tsRowsInFileBlock;                         //
  if (pCreate->cacheNumOfBlocks.fraction < 0) pCreate->cacheNumOfBlocks.fraction = tsAverageCacheBlocks;  //
  //-1 for balance

#ifdef CLUSTER
  if (pCreate->replications > TSDB_VNODES_SUPPORT - 1) pCreate->replications = TSDB_VNODES_SUPPORT - 1;
#else
  pCreate->replications = 1;
#endif

  if (pCreate->commitLog < 0 || pCreate->commitLog > 1) {
    mTrace("invalid db option commitLog: %d", pCreate->commitLog);
    return TSDB_CODE_INVALID_OPTION;
  }
  
  if (pCreate->replications < TSDB_REPLICA_MIN_NUM || pCreate->replications > TSDB_REPLICA_MAX_NUM) {
    mTrace("invalid db option replications: %d", pCreate->replications);
    return TSDB_CODE_INVALID_OPTION;
  }

  if (pCreate->daysPerFile < TSDB_FILE_MIN_PARTITION_RANGE || pCreate->daysPerFile > TSDB_FILE_MAX_PARTITION_RANGE) {
    mTrace("invalid db option daysPerFile: %d valid range: %d--%d", pCreate->daysPerFile, TSDB_FILE_MIN_PARTITION_RANGE,
           TSDB_FILE_MAX_PARTITION_RANGE);
    return TSDB_CODE_INVALID_OPTION;
  }

  if (pCreate->daysToKeep1 > pCreate->daysToKeep2 || pCreate->daysToKeep2 > pCreate->daysToKeep) {
    mTrace("invalid db option daystokeep1: %d, daystokeep2: %d, daystokeep: %d", pCreate->daysToKeep1,
           pCreate->daysToKeep2, pCreate->daysToKeep);
    return TSDB_CODE_INVALID_OPTION;
  }

  if (pCreate->daysToKeep1 < TSDB_FILE_MIN_PARTITION_RANGE || pCreate->daysToKeep1 < pCreate->daysPerFile) {
    mTrace("invalid db option daystokeep: %d", pCreate->daysToKeep);
    return TSDB_CODE_INVALID_OPTION;
  }
  if (pCreate->rowsInFileBlock < TSDB_MIN_ROWS_IN_FILEBLOCK || pCreate->rowsInFileBlock > TSDB_MAX_ROWS_IN_FILEBLOCK) {
    mTrace("invalid db option rowsInFileBlock: %d valid range: %d--%d", pCreate->rowsInFileBlock,
           TSDB_MIN_ROWS_IN_FILEBLOCK, TSDB_MAX_ROWS_IN_FILEBLOCK);
    return TSDB_CODE_INVALID_OPTION;
  }
  if (pCreate->cacheBlockSize < TSDB_MIN_CACHE_BLOCK_SIZE || pCreate->cacheBlockSize > TSDB_MAX_CACHE_BLOCK_SIZE) {
    mTrace("invalid db option cacheBlockSize: %d valid range: %d--%d", pCreate->cacheBlockSize,
           TSDB_MIN_CACHE_BLOCK_SIZE, TSDB_MAX_CACHE_BLOCK_SIZE);
    return TSDB_CODE_INVALID_OPTION;
  }
  if (pCreate->maxSessions < TSDB_MIN_TABLES_PER_VNODE || pCreate->maxSessions > TSDB_MAX_TABLES_PER_VNODE) {
    mTrace("invalid db option maxSessions: %d valid range: %d--%d", pCreate->maxSessions, TSDB_MIN_TABLES_PER_VNODE,
           TSDB_MAX_TABLES_PER_VNODE);
    return TSDB_CODE_INVALID_OPTION;
  }

  if (pCreate->precision != TSDB_TIME_PRECISION_MILLI && pCreate->precision != TSDB_TIME_PRECISION_MICRO) {
    mTrace("invalid db option timePrecision: %d valid value: %d,%d", pCreate->precision, TSDB_TIME_PRECISION_MILLI,
           TSDB_TIME_PRECISION_MICRO);
    return TSDB_CODE_INVALID_OPTION;
  }

  if (pCreate->cacheNumOfBlocks.fraction < 0 || pCreate->cacheNumOfBlocks.fraction > TSDB_MAX_AVG_BLOCKS) {
    mTrace("invalid db option ablocks: %d valid value: %d,%d", pCreate->precision, 0, TSDB_MAX_AVG_BLOCKS);
    return TSDB_CODE_INVALID_OPTION;
  } else {
    pCreate->cacheNumOfBlocks.totalBlocks = (int32_t)(pCreate->cacheNumOfBlocks.fraction * pCreate->maxSessions);
  }

  if (pCreate->cacheNumOfBlocks.totalBlocks > TSDB_MAX_CACHE_BLOCKS) {
    mTrace("invalid db option cacheNumOfBlocks: %d valid range: %d", pCreate->cacheNumOfBlocks.totalBlocks,
           TSDB_MAX_CACHE_BLOCKS);
    return TSDB_CODE_INVALID_OPTION;
  }

  if (pCreate->commitTime < TSDB_MIN_COMMIT_TIME_INTERVAL || pCreate->commitTime > TSDB_MAX_COMMIT_TIME_INTERVAL) {
    mTrace("invalid db option commitTime: %d valid range: %d-%d", pCreate->commitTime, TSDB_MIN_COMMIT_TIME_INTERVAL,
           TSDB_MAX_COMMIT_TIME_INTERVAL);
    return TSDB_CODE_INVALID_OPTION;
  }
  if (pCreate->compression > TSDB_MAX_COMPRESSION_LEVEL) {
    mTrace("invalid db option compression: %d", pCreate->compression, TSDB_MIN_COMMIT_TIME_INTERVAL,
           TSDB_MAX_COMMIT_TIME_INTERVAL);
    return TSDB_CODE_INVALID_OPTION;
  }

  if (pCreate->blocksPerMeter < 0) pCreate->blocksPerMeter = pCreate->cacheNumOfBlocks.totalBlocks / 4;
  if (pCreate->blocksPerMeter > pCreate->cacheNumOfBlocks.totalBlocks * 3 / 4) {
    pCreate->blocksPerMeter = pCreate->cacheNumOfBlocks.totalBlocks * 3 / 4;
  }
  if (pCreate->blocksPerMeter < 4) pCreate->blocksPerMeter = 4;

  pCreate->maxSessions++;

  return TSDB_CODE_SUCCESS;
}