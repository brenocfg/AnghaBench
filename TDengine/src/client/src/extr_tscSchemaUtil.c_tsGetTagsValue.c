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
typedef  int uint32_t ;
typedef  int int32_t ;
struct TYPE_3__ {int numOfColumns; int numOfTags; } ;
typedef  int /*<<< orphan*/  SSchema ;
typedef  TYPE_1__ SMeterMeta ;

/* Variables and functions */

char* tsGetTagsValue(SMeterMeta* pMeta) {
  int32_t  numOfTotalCols = pMeta->numOfColumns + pMeta->numOfTags;
  uint32_t offset = sizeof(SMeterMeta) + numOfTotalCols * sizeof(SSchema);

  return ((char*)pMeta + offset);
}