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
struct TYPE_5__ {size_t totalEntries; TYPE_1__* pNode; } ;
struct TYPE_4__ {int index; } ;
typedef  TYPE_2__ SLoserTreeInfo ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void tLoserTreeDisplay(SLoserTreeInfo* pTree) {
  printf("the value of loser tree:\t");
  for (int32_t i = 0; i < pTree->totalEntries; ++i) printf("%d\t", pTree->pNode[i].index);
  printf("\n");
}