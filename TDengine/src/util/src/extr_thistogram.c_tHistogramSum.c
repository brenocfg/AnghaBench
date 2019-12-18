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
typedef  int /*<<< orphan*/  int64_t ;
typedef  size_t int32_t ;
struct TYPE_5__ {double val; double num; } ;
struct TYPE_4__ {size_t numOfEntries; TYPE_2__* elems; } ;
typedef  TYPE_1__ SHistogramInfo ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 size_t vnodeHistobinarySearch (TYPE_2__*,size_t,double) ; 

int64_t tHistogramSum(SHistogramInfo* pHisto, double v) {
#if defined(USE_ARRAYLIST)
  int32_t slotIdx = vnodeHistobinarySearch(pHisto->elems, pHisto->numOfEntries, v);
  if (pHisto->elems[slotIdx].val != v) {
    slotIdx -= 1;

    if (slotIdx < 0) {
      slotIdx = 0;
      assert(v <= pHisto->elems[slotIdx].val);
    } else {
      assert(v >= pHisto->elems[slotIdx].val);

      if (slotIdx + 1 < pHisto->numOfEntries) {
        assert(v < pHisto->elems[slotIdx + 1].val);
      }
    }
  }

  double m1 = pHisto->elems[slotIdx].num;
  double v1 = pHisto->elems[slotIdx].val;

  double m2 = pHisto->elems[slotIdx + 1].num;
  double v2 = pHisto->elems[slotIdx + 1].val;

  double estNum = m1 + (m2 - m1) * (v - v1) / (v2 - v1);
  double s1 = (m1 + estNum) * (v - v1) / (2 * (v2 - v1));

  for (int32_t i = 0; i < slotIdx; ++i) {
    s1 += pHisto->elems[i].num;
  }

  s1 = s1 + m1 / 2;

  return (int64_t)s1;
#endif
}