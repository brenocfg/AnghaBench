#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_5__ {int totalEntries; int numOfEntries; TYPE_1__* pNode; } ;
struct TYPE_4__ {int index; } ;
typedef  TYPE_2__ SLoserTreeInfo ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void tLoserTreeInit(SLoserTreeInfo* pTree) {
  assert((pTree->totalEntries & 0x01) == 0 && (pTree->numOfEntries << 1 == pTree->totalEntries));

  for (int32_t i = 0; i < pTree->totalEntries; ++i) {
    if (i < pTree->numOfEntries) {
      pTree->pNode[i].index = -1;
    } else {
      pTree->pNode[i].index = i - pTree->numOfEntries;
    }
  }
}