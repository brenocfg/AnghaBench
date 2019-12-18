#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct TYPE_11__** pForward; scalar_t__ pData; } ;
typedef  TYPE_4__ tSkipListNode ;
typedef  int int32_t ;
struct TYPE_13__ {double val; int /*<<< orphan*/  num; } ;
struct TYPE_12__ {int numOfEntries; int numOfElems; TYPE_3__* pList; TYPE_1__* elems; } ;
struct TYPE_9__ {TYPE_4__** pForward; } ;
struct TYPE_10__ {TYPE_2__ pHead; } ;
struct TYPE_8__ {double val; int /*<<< orphan*/  num; } ;
typedef  TYPE_5__ SHistogramInfo ;
typedef  TYPE_6__ SHistBin ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,double,...) ; 

void tHistogramPrint(SHistogramInfo* pHisto) {
  printf("total entries: %d, elements: %d\n", pHisto->numOfEntries, pHisto->numOfElems);
#if defined(USE_ARRAYLIST)
  for (int32_t i = 0; i < pHisto->numOfEntries; ++i) {
    printf("%d: (%f, %lld)\n", i + 1, pHisto->elems[i].val, pHisto->elems[i].num);
  }
#else
  tSkipListNode* pNode = pHisto->pList->pHead.pForward[0];

  for (int32_t i = 0; i < pHisto->numOfEntries; ++i) {
    SHistBin* pEntry = (SHistBin*)pNode->pData;
    printf("%d: (%f, %lld)\n", i + 1, pEntry->val, pEntry->num);
    pNode = pNode->pForward[0];
  }
#endif
}