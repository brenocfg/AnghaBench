#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_13__ {scalar_t__ val; scalar_t__ num; } ;
struct TYPE_12__ {int numOfEntries; scalar_t__ min; scalar_t__ max; TYPE_2__* elems; scalar_t__ numOfElems; } ;
typedef  TYPE_1__ SHistogramInfo ;
typedef  TYPE_2__ SHistBin ;

/* Variables and functions */
 int MAX_HISTOGRAM_BIN ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  histogramMergeImpl (TYPE_2__*,size_t*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 TYPE_1__* tHistogramCreate (size_t) ; 

SHistogramInfo* tHistogramMerge(SHistogramInfo* pHisto1, SHistogramInfo* pHisto2, int32_t numOfEntries) {
  SHistogramInfo* pResHistogram = tHistogramCreate(numOfEntries);

  // error in histogram info
  if (pHisto1->numOfEntries > MAX_HISTOGRAM_BIN || pHisto2->numOfEntries > MAX_HISTOGRAM_BIN) {
    return pResHistogram;
  }

  SHistBin* pHistoBins = calloc(1, sizeof(SHistBin) * (pHisto1->numOfEntries + pHisto2->numOfEntries));
  int32_t i = 0, j = 0, k = 0;

  while (i < pHisto1->numOfEntries && j < pHisto2->numOfEntries) {
    if (pHisto1->elems[i].val < pHisto2->elems[j].val) {
      pHistoBins[k++] = pHisto1->elems[i++];
    } else if (pHisto1->elems[i].val > pHisto2->elems[j].val) {
      pHistoBins[k++] = pHisto2->elems[j++];
    } else {
      pHistoBins[k] = pHisto1->elems[i++];
      pHistoBins[k++].num += pHisto2->elems[j++].num;
    }
  }

  if (i < pHisto1->numOfEntries) {
    int32_t remain = pHisto1->numOfEntries - i;
    memcpy(&pHistoBins[k], &pHisto1->elems[i], sizeof(SHistBin) * remain);
    k += remain;
  }

  if (j < pHisto2->numOfEntries) {
    int32_t remain = pHisto2->numOfEntries - j;
    memcpy(&pHistoBins[k], &pHisto2->elems[j], sizeof(SHistBin) * remain);
    k += remain;
  }

  /* update other information */
  pResHistogram->numOfElems = pHisto1->numOfElems + pHisto2->numOfElems;
  pResHistogram->min = (pHisto1->min < pHisto2->min) ? pHisto1->min : pHisto2->min;
  pResHistogram->max = (pHisto1->max > pHisto2->max) ? pHisto1->max : pHisto2->max;

  while (k > numOfEntries) {
    histogramMergeImpl(pHistoBins, &k);
  }

  pResHistogram->numOfEntries = k;
  memcpy(pResHistogram->elems, pHistoBins, sizeof(SHistBin) * k);

  free(pHistoBins);
  return pResHistogram;
}