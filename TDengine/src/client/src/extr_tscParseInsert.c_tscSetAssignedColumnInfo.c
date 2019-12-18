#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_8__ {size_t numOfCols; size_t numOfAssignedCols; int* hasVal; TYPE_1__* elems; } ;
struct TYPE_7__ {scalar_t__ bytes; } ;
struct TYPE_6__ {size_t colIndex; scalar_t__ offset; } ;
typedef  TYPE_2__ SSchema ;
typedef  TYPE_3__ SParsedDataColInfo ;

/* Variables and functions */

__attribute__((used)) static void tscSetAssignedColumnInfo(SParsedDataColInfo *spd, SSchema *pSchema, int32_t numOfCols) {
  spd->numOfCols = numOfCols;
  spd->numOfAssignedCols = numOfCols;

  for (int32_t i = 0; i < numOfCols; ++i) {
    spd->hasVal[i] = true;
    spd->elems[i].colIndex = i;

    if (i > 0) {
      spd->elems[i].offset = spd->elems[i - 1].offset + pSchema[i - 1].bytes;
    }
  }
}