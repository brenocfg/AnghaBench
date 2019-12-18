#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_2__ {scalar_t__ offsetInHeaderFile; } ;
typedef  TYPE_1__ SMeterDataInfo ;

/* Variables and functions */

__attribute__((used)) static int32_t offsetComparator(const void *pLeft, const void *pRight) {
  SMeterDataInfo **pLeft1 = (SMeterDataInfo **)pLeft;
  SMeterDataInfo **pRight1 = (SMeterDataInfo **)pRight;

  if ((*pLeft1)->offsetInHeaderFile == (*pRight1)->offsetInHeaderFile) {
    return 0;
  }

  return ((*pLeft1)->offsetInHeaderFile > (*pRight1)->offsetInHeaderFile) ? 1 : -1;
}