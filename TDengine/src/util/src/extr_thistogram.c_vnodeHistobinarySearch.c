#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {double val; } ;
typedef  TYPE_1__ SHistBin ;

/* Variables and functions */

int32_t vnodeHistobinarySearch(SHistBin* pEntry, int32_t len, double val) {
  int32_t end = len - 1;
  int32_t start = 0;

  while (start <= end) {
    int32_t mid = (end - start) / 2 + start;
    if (pEntry[mid].val == val) {
      return mid;
    }

    if (pEntry[mid].val < val) {
      start = mid + 1;
    } else {
      end = mid - 1;
    }
  }

  int32_t ret = start > end ? start : end;
  if (ret < 0) {
    return 0;
  } else {
    return ret;
  }
}