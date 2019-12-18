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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_5__ {scalar_t__ offset; } ;
struct TYPE_6__ {TYPE_1__ limit; } ;
typedef  TYPE_2__ SQuery ;

/* Variables and functions */
 int /*<<< orphan*/  vnodeDoFilterData (TYPE_2__*,int /*<<< orphan*/ ) ; 

bool vnodeFilterData(SQuery* pQuery, int32_t* numOfActualRead, int32_t index) {
  (*numOfActualRead)++;
  if (!vnodeDoFilterData(pQuery, index)) {
    return false;
  }

  if (pQuery->limit.offset > 0) {
    pQuery->limit.offset--;  // ignore this qualified row
    return false;
  }

  return true;
}