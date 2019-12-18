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
typedef  scalar_t__ int8_t ;
struct TYPE_4__ {scalar_t__ lowerBndi; } ;
struct TYPE_5__ {TYPE_1__ filterInfo; } ;
typedef  TYPE_2__ SColumnFilterElem ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

bool equal_i8(SColumnFilterElem *pFilter, char *minval, char *maxval) {
  if (*(int8_t *)minval == *(int8_t *)maxval) {
    return (*(int8_t *)minval == pFilter->filterInfo.lowerBndi);
  } else { /* range filter */
    assert(*(int8_t *)minval < *(int8_t *)maxval);

    return *(int8_t *)minval <= pFilter->filterInfo.lowerBndi && *(int8_t *)maxval >= pFilter->filterInfo.lowerBndi;
  }
}