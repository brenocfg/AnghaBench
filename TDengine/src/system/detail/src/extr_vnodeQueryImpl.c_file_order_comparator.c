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
struct TYPE_2__ {scalar_t__ fileID; } ;
typedef  TYPE_1__ SQueryFileInfo ;

/* Variables and functions */

__attribute__((used)) static int file_order_comparator(const void *p1, const void *p2) {
  SQueryFileInfo *pInfo1 = (SQueryFileInfo *)p1;
  SQueryFileInfo *pInfo2 = (SQueryFileInfo *)p2;

  if (pInfo1->fileID == pInfo2->fileID) {
    return 0;
  }

  return (pInfo1->fileID > pInfo2->fileID) ? 1 : -1;
}