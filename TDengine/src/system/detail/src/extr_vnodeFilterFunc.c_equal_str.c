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
struct TYPE_4__ {scalar_t__ len; scalar_t__ pz; } ;
struct TYPE_5__ {scalar_t__ bytes; TYPE_1__ filterInfo; } ;
typedef  TYPE_2__ SColumnFilterElem ;

/* Variables and functions */
 scalar_t__ strncmp (char*,char*,scalar_t__) ; 

bool equal_str(SColumnFilterElem *pFilter, char *minval, char *maxval) {
  // query condition string is greater than the max length of string, not qualified data
  if (pFilter->filterInfo.len > pFilter->bytes) {
    return false;
  }

  return strncmp((char *)pFilter->filterInfo.pz, minval, pFilter->bytes) == 0;
}