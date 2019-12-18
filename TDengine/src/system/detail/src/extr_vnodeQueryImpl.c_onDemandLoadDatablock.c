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
typedef  int int16_t ;
struct TYPE_3__ {scalar_t__ nAggTimeInterval; } ;
typedef  TYPE_1__ SQuery ;

/* Variables and functions */

bool onDemandLoadDatablock(SQuery *pQuery, int16_t queryRangeSet) {
  return (pQuery->nAggTimeInterval == 0) || ((queryRangeSet == 1) && (pQuery->nAggTimeInterval > 0));
}