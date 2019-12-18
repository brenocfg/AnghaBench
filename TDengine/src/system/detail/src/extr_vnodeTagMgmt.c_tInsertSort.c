#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ int32_t ;
typedef  int (* __ext_compar_fn_t ) (void*,void*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_DATA_TYPE_BINARY ; 
 int /*<<< orphan*/  tsDataSwap (void**,void**,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void tInsertSort(void **pMeterSids, size_t size, int32_t startPos, int32_t endPos, void *param,
                        __ext_compar_fn_t compareFn) {
  for (int32_t i = startPos + 1; i <= endPos; ++i) {
    for (int32_t j = i; j > startPos; --j) {
      if (compareFn(pMeterSids[j], pMeterSids[j - 1], param) == -1) {
        tsDataSwap(&pMeterSids[j], &pMeterSids[j - 1], TSDB_DATA_TYPE_BINARY, size);
      } else {
        break;
      }
    }
  }
}