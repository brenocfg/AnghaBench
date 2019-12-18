#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_5__ {scalar_t__ len; struct TYPE_5__* pz; } ;
struct TYPE_4__ {scalar_t__ numOfFilters; scalar_t__ type; TYPE_3__* filters; } ;
typedef  TYPE_1__ SColumnInfo ;

/* Variables and functions */
 scalar_t__ TSDB_DATA_TYPE_BINARY ; 
 int /*<<< orphan*/  tfree (TYPE_3__*) ; 

void vnodeFreeColumnInfo(SColumnInfo* pColumnInfo) {
  if (pColumnInfo == NULL) {
    return;
  }

  if (pColumnInfo->numOfFilters > 0) {
    if (pColumnInfo->type == TSDB_DATA_TYPE_BINARY) {
      for (int32_t i = 0; i < pColumnInfo->numOfFilters; ++i) {
        tfree(pColumnInfo->filters[i].pz);
        pColumnInfo->filters[i].len = 0;
      }
    }

    tfree(pColumnInfo->filters);
  }
}