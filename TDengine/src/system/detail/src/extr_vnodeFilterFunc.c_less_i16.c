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
typedef  scalar_t__ int16_t ;
struct TYPE_4__ {scalar_t__ upperBndi; } ;
struct TYPE_5__ {TYPE_1__ filterInfo; } ;
typedef  TYPE_2__ SColumnFilterElem ;

/* Variables and functions */

bool less_i16(SColumnFilterElem *pFilter, char *minval, char *maxval) {
  return (*(int16_t *)minval < pFilter->filterInfo.upperBndi);
}