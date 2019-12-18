#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ keyFirst; scalar_t__ keyLast; } ;
struct TYPE_6__ {scalar_t__ lastKey; scalar_t__ ekey; } ;
typedef  TYPE_1__ SQuery ;
typedef  TYPE_2__ SBlockInfo ;

/* Variables and functions */
 scalar_t__ requireTimestamp (TYPE_1__*) ; 

bool needPrimaryTimestampCol(SQuery *pQuery, SBlockInfo *pBlockInfo) {
  /*
   * 1. if skey or ekey locates in this block, we need to load the timestamp column to decide the precise position
   * 2. if there are top/bottom, first_dst/last_dst functions, we need to load timestamp column in any cases;
   */
  bool loadPrimaryTS = (pQuery->lastKey >= pBlockInfo->keyFirst && pQuery->lastKey <= pBlockInfo->keyLast) ||
                       (pQuery->ekey >= pBlockInfo->keyFirst && pQuery->ekey <= pBlockInfo->keyLast) ||
                       requireTimestamp(pQuery);

  return loadPrimaryTS;
}