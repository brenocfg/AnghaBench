#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* int32_t ;
struct TYPE_4__ {int tsSource; int /*<<< orphan*/  meterId; void* size; void* rowSize; } ;
typedef  TYPE_1__ STableDataBlocks ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_METER_ID_LEN ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* tscCreateDataBlock (size_t) ; 

STableDataBlocks* tscCreateDataBlockEx(size_t size, int32_t rowSize, int32_t startOffset, char* name) {
  STableDataBlocks* dataBuf = tscCreateDataBlock(size);

  dataBuf->rowSize = rowSize;
  dataBuf->size = startOffset;
  dataBuf->tsSource = -1;

  strncpy(dataBuf->meterId, name, TSDB_METER_ID_LEN);
  return dataBuf;
}