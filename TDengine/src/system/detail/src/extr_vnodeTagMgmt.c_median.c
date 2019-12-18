#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  orderIdx; int /*<<< orphan*/  pTagSchema; } ;
typedef  TYPE_1__ tOrderDescriptor ;
typedef  int int32_t ;
typedef  int (* __ext_compar_fn_t ) (void*,void*,TYPE_1__*) ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_DATA_TYPE_BINARY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tTagsPrints (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsDataSwap (void**,void**,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void median(void **pMeterSids, size_t size, int32_t s1, int32_t s2, tOrderDescriptor *pOrderDesc,
                   __ext_compar_fn_t compareFn) {
  int32_t midIdx = ((s2 - s1) >> 1) + s1;

  if (compareFn(pMeterSids[midIdx], pMeterSids[s1], pOrderDesc) == 1) {
    tsDataSwap(&pMeterSids[midIdx], &pMeterSids[s1], TSDB_DATA_TYPE_BINARY, size);
  }

  if (compareFn(pMeterSids[midIdx], pMeterSids[s2], pOrderDesc) == 1) {
    tsDataSwap(&pMeterSids[midIdx], &pMeterSids[s1], TSDB_DATA_TYPE_BINARY, size);
    tsDataSwap(&pMeterSids[midIdx], &pMeterSids[s2], TSDB_DATA_TYPE_BINARY, size);
  } else if (compareFn(pMeterSids[s1], pMeterSids[s2], pOrderDesc) == 1) {
    tsDataSwap(&pMeterSids[s1], &pMeterSids[s2], TSDB_DATA_TYPE_BINARY, size);
  }

  assert(compareFn(pMeterSids[midIdx], pMeterSids[s1], pOrderDesc) <= 0 &&
         compareFn(pMeterSids[s1], pMeterSids[s2], pOrderDesc) <= 0);

#ifdef _DEBUG_VIEW
  tTagsPrints(pMeterSids[s1], pOrderDesc->pTagSchema, &pOrderDesc->orderIdx);
  tTagsPrints(pMeterSids[midIdx], pOrderDesc->pTagSchema, &pOrderDesc->orderIdx);
  tTagsPrints(pMeterSids[s2], pOrderDesc->pTagSchema, &pOrderDesc->orderIdx);
#endif
}