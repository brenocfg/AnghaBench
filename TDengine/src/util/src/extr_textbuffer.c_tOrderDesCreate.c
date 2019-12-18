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
struct TYPE_4__ {int numOfOrderedCols; int* pData; } ;
struct TYPE_5__ {int tsOrder; TYPE_1__ orderIdx; int /*<<< orphan*/ * pSchema; } ;
typedef  TYPE_2__ tOrderDescriptor ;
typedef  int /*<<< orphan*/  tColModel ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 

tOrderDescriptor *tOrderDesCreate(int32_t *orderColIdx, int32_t numOfOrderCols, tColModel *pModel,
                                  int32_t tsOrderType) {
  tOrderDescriptor *desc = (tOrderDescriptor *)malloc(sizeof(tOrderDescriptor) + sizeof(int32_t) * numOfOrderCols);
  if (desc == NULL) {
    return NULL;
  }

  desc->pSchema = pModel;
  desc->tsOrder = tsOrderType;

  desc->orderIdx.numOfOrderedCols = numOfOrderCols;
  for (int32_t i = 0; i < numOfOrderCols; ++i) {
    desc->orderIdx.pData[i] = orderColIdx[i];
  }

  return desc;
}