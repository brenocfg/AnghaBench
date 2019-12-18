#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_3__ {int ordered; int tsSource; scalar_t__ prevTS; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_1__ STableDataBlocks ;

/* Variables and functions */
 int TSDB_CODE_SUCCESS ; 
 int TSDB_USE_CLI_TS ; 
 int TSDB_USE_SERVER_TS ; 

__attribute__((used)) static int32_t tsCheckTimestamp(STableDataBlocks *pDataBlocks, const char *start) {
  // once the data block is disordered, we do NOT keep previous timestamp any more
  if (!pDataBlocks->ordered) {
    return TSDB_CODE_SUCCESS;
  }

  TSKEY k = *(TSKEY *)start;

  if (k == 0) {
    if (pDataBlocks->tsSource == TSDB_USE_CLI_TS) {
      return -1;
    } else if (pDataBlocks->tsSource == -1) {
      pDataBlocks->tsSource = TSDB_USE_SERVER_TS;
    }
  } else {
    if (pDataBlocks->tsSource == TSDB_USE_SERVER_TS) {
      return -1;
    } else if (pDataBlocks->tsSource == -1) {
      pDataBlocks->tsSource = TSDB_USE_CLI_TS;
    }
  }

  if (k <= pDataBlocks->prevTS && (pDataBlocks->tsSource == TSDB_USE_CLI_TS)) {
    pDataBlocks->ordered = false;
  }

  pDataBlocks->prevTS = k;
  return TSDB_CODE_SUCCESS;
}