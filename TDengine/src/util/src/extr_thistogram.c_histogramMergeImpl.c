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
typedef  size_t int32_t ;
struct TYPE_5__ {double val; double num; } ;
typedef  TYPE_1__ SHistBin ;

/* Variables and functions */
 double DBL_MAX ; 
 int /*<<< orphan*/  memmove (TYPE_1__*,TYPE_1__*,size_t) ; 

__attribute__((used)) static void histogramMergeImpl(SHistBin* pHistBin, int32_t* size) {
#if defined(USE_ARRAYLIST)
  int32_t oldSize = *size;

  double  delta = DBL_MAX;
  int32_t index = -1;
  for (int32_t i = 1; i < oldSize; ++i) {
    double d = pHistBin[i].val - pHistBin[i - 1].val;
    if (d < delta) {
      delta = d;
      index = i - 1;
    }
  }

  SHistBin* s1 = &pHistBin[index];
  SHistBin* s2 = &pHistBin[index + 1];

  double newVal = (s1->val * s1->num + s2->val * s2->num) / (s1->num + s2->num);
  s1->val = newVal;
  s1->num = s1->num + s2->num;

  memmove(&pHistBin[index + 1], &pHistBin[index + 2], (oldSize - index - 2) * sizeof(SHistBin));
  (*size) -= 1;
#endif
}