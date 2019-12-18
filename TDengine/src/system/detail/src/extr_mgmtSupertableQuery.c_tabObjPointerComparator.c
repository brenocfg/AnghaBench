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
typedef  scalar_t__ int64_t ;
typedef  int int32_t ;

/* Variables and functions */

__attribute__((used)) static int32_t tabObjPointerComparator(const void* pLeft, const void* pRight) {
  int64_t ret = (int64_t)pLeft - (int64_t)pRight;
  if (ret == 0) {
    return 0;
  } else {
    return ret > 0 ? 1 : -1;
  }
}