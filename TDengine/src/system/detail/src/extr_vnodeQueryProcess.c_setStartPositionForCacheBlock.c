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
struct TYPE_7__ {scalar_t__ numOfPoints; } ;
struct TYPE_6__ {scalar_t__ pos; } ;
typedef  TYPE_1__ SQuery ;
typedef  TYPE_2__ SCacheBlock ;

/* Variables and functions */
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_1__*) ; 

__attribute__((used)) static void setStartPositionForCacheBlock(SQuery *pQuery, SCacheBlock *pBlock, bool *firstCheckSlot) {
  if (!(*firstCheckSlot)) {
    if (QUERY_IS_ASC_QUERY(pQuery)) {
      pQuery->pos = 0;
    } else {
      pQuery->pos = pBlock->numOfPoints - 1;
    }
  } else {
    (*firstCheckSlot) = false;
  }
}