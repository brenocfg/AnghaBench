#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_5__ {int totalEntries; scalar_t__ numOfEntries; } ;
typedef  TYPE_1__ SLoserTreeInfo ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tLoserTreeAdjust (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  tLoserTreeInit (TYPE_1__*) ; 

void tLoserTreeRebuild(SLoserTreeInfo* pTree) {
  assert((pTree->totalEntries & 0x1) == 0);

  tLoserTreeInit(pTree);
  for (int32_t i = pTree->totalEntries - 1; i >= pTree->numOfEntries; i--) {
    tLoserTreeAdjust(pTree, i);
  }
}