#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_7__ {int num; double val; } ;
struct TYPE_6__ {int numOfEntries; int maxEntries; TYPE_2__* elems; } ;
typedef  TYPE_1__ SHistogramInfo ;
typedef  int /*<<< orphan*/  SHistBin ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  histogramMergeImpl (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  memmove (TYPE_2__*,TYPE_2__*,int) ; 

int32_t histogramCreateBin(SHistogramInfo* pHisto, int32_t index, double val) {
#if defined(USE_ARRAYLIST)
  int32_t remain = pHisto->numOfEntries - index;
  if (remain > 0) {
    memmove(&pHisto->elems[index + 1], &pHisto->elems[index], sizeof(SHistBin) * remain);
  }

  assert(index >= 0 && index <= pHisto->maxEntries);

  pHisto->elems[index].num = 1;
  pHisto->elems[index].val = val;
  pHisto->numOfEntries += 1;

  /* we need to merge the slot */
  if (pHisto->numOfEntries == pHisto->maxEntries + 1) {
    histogramMergeImpl(pHisto->elems, &pHisto->numOfEntries);

    pHisto->elems[pHisto->maxEntries].val = 0;
    pHisto->elems[pHisto->maxEntries].num = 0;
  }
#endif
  assert(pHisto->numOfEntries <= pHisto->maxEntries);
  return 0;
}