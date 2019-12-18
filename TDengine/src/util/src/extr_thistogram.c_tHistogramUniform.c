#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ pData; struct TYPE_11__** pForward; } ;
typedef  TYPE_4__ tSkipListNode ;
typedef  double int64_t ;
typedef  int int32_t ;
struct TYPE_13__ {double num; double val; } ;
struct TYPE_12__ {double numOfElems; double min; double max; int numOfEntries; TYPE_3__* pList; TYPE_1__* elems; } ;
struct TYPE_9__ {TYPE_4__** pForward; } ;
struct TYPE_10__ {TYPE_2__ pHead; } ;
struct TYPE_8__ {double num; double val; } ;
typedef  TYPE_5__ SHistogramInfo ;
typedef  TYPE_6__ SHistBin ;

/* Variables and functions */
 scalar_t__ FLT_EPSILON ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fabs (double) ; 
 double* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,double,double,double) ; 
 int sqrt (int) ; 

double* tHistogramUniform(SHistogramInfo* pHisto, double* ratio, int32_t num) {
#if defined(USE_ARRAYLIST)
  double* pVal = malloc(num * sizeof(double));

  for (int32_t i = 0; i < num; ++i) {
    double numOfElem = (ratio[i] / 100) * pHisto->numOfElems;

    if (numOfElem == 0) {
      pVal[i] = pHisto->min;
      continue;
    } else if (numOfElem <= pHisto->elems[0].num) {
      pVal[i] = pHisto->elems[0].val;
      continue;
    } else if (numOfElem == pHisto->numOfElems) {
      pVal[i] = pHisto->max;
      continue;
    }

    int32_t j = 0;
    int64_t total = 0;

    while (j < pHisto->numOfEntries) {
      total += pHisto->elems[j].num;
      if (total <= numOfElem && total + pHisto->elems[j + 1].num > numOfElem) {
        break;
      }

      j += 1;
    }

    assert(total <= numOfElem && total + pHisto->elems[j + 1].num > numOfElem);

    double delta = numOfElem - total;
    if (fabs(delta) < FLT_EPSILON) {
      pVal[i] = pHisto->elems[j].val;
    }

    double start = pHisto->elems[j].num;
    double range = pHisto->elems[j + 1].num - start;

    if (range == 0) {
      pVal[i] = (pHisto->elems[j + 1].val - pHisto->elems[j].val) * delta / start + pHisto->elems[j].val;
    } else {
      double factor = (-2 * start + sqrt(4 * start * start - 4 * range * (-2 * delta))) / (2 * range);
      pVal[i] = pHisto->elems[j].val + (pHisto->elems[j + 1].val - pHisto->elems[j].val) * factor;
    }
  }
#else
  double* pVal = malloc(num * sizeof(double));

  for (int32_t i = 0; i < num; ++i) {
    double numOfElem = ratio[i] * pHisto->numOfElems;

    tSkipListNode* pFirst = pHisto->pList->pHead.pForward[0];
    SHistBin*      pEntry = (SHistBin*)pFirst->pData;
    if (numOfElem == 0) {
      pVal[i] = pHisto->min;
      printf("i/numofSlot: %f, v:%f, %f\n", ratio[i], numOfElem, pVal[i]);
      continue;
    } else if (numOfElem <= pEntry->num) {
      pVal[i] = pEntry->val;
      printf("i/numofSlot: %f, v:%f, %f\n", ratio[i], numOfElem, pVal[i]);
      continue;
    } else if (numOfElem == pHisto->numOfElems) {
      pVal[i] = pHisto->max;
      printf("i/numofSlot: %f, v:%f, %f\n", ratio[i], numOfElem, pVal[i]);
      continue;
    }

    int32_t   j = 0;
    int64_t   total = 0;
    SHistBin* pPrev = pEntry;

    while (j < pHisto->numOfEntries) {
      if (total <= numOfElem && total + pEntry->num > numOfElem) {
        break;
      }

      total += pEntry->num;
      pPrev = pEntry;

      pFirst = pFirst->pForward[0];
      pEntry = (SHistBin*)pFirst->pData;

      j += 1;
    }

    assert(total <= numOfElem && total + pEntry->num > numOfElem);

    double delta = numOfElem - total;
    if (fabs(delta) < FLT_EPSILON) {
      //                printf("i/numofSlot: %f, v:%f, %f\n",
      //                (double)i/numOfSlots, numOfElem, pHisto->elems[j].val);
      pVal[i] = pPrev->val;
    }

    double start = pPrev->num;
    double range = pEntry->num - start;

    if (range == 0) {
      pVal[i] = (pEntry->val - pPrev->val) * delta / start + pPrev->val;
    } else {
      double factor = (-2 * start + sqrt(4 * start * start - 4 * range * (-2 * delta))) / (2 * range);
      pVal[i] = pPrev->val + (pEntry->val - pPrev->val) * factor;
    }
    //            printf("i/numofSlot: %f, v:%f, %f\n", (double)i/numOfSlots,
    //            numOfElem, val);
  }
#endif
  return pVal;
}