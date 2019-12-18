#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_6__ {scalar_t__ bytes; } ;
struct TYPE_5__ {scalar_t__ numOfColumns; scalar_t__ numOfTags; scalar_t__ schema; } ;
typedef  TYPE_1__ STabObj ;
typedef  TYPE_2__ SSchema ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ mgmtIsMetric (TYPE_1__*) ; 

int32_t mgmtGetTagsLength(STabObj* pMetric, int32_t col) {  // length before column col
  assert(mgmtIsMetric(pMetric) && col >= 0);

  int32_t len = 0;
  int32_t tagColumnIndexOffset = pMetric->numOfColumns;

  for (int32_t i = 0; i < pMetric->numOfTags && i < col; ++i) {
    len += ((SSchema*)pMetric->schema)[tagColumnIndexOffset + i].bytes;
  }

  return len;
}