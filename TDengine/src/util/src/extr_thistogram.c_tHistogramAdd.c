#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_21__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {double dKey; } ;
struct TYPE_28__ {scalar_t__ pData; TYPE_3__** pBackward; struct TYPE_28__** pForward; TYPE_1__ key; } ;
typedef  TYPE_4__ tSkipListNode ;
typedef  int /*<<< orphan*/  tSkipListKey ;
typedef  size_t int32_t ;
struct TYPE_27__ {scalar_t__ pData; TYPE_4__** pForward; } ;
struct TYPE_33__ {TYPE_3__ pHead; } ;
struct TYPE_32__ {double val; int num; } ;
struct TYPE_31__ {double val; int index; scalar_t__ num; size_t delta; } ;
struct TYPE_30__ {int numOfEntries; size_t maxEntries; int numOfElems; int ordered; size_t maxIndex; double max; double min; TYPE_9__* pList; TYPE_5__* pLoserTree; TYPE_8__* elems; } ;
struct TYPE_29__ {size_t numOfEntries; size_t totalEntries; TYPE_2__* pNode; } ;
struct TYPE_26__ {int index; TYPE_4__* pData; } ;
struct TYPE_25__ {int /*<<< orphan*/  nSize; } ;
typedef  TYPE_5__ SLoserTreeInfo ;
typedef  TYPE_6__ SHistogramInfo ;
typedef  TYPE_7__ SHistBin ;

/* Variables and functions */
 void* DBL_MAX ; 
 int /*<<< orphan*/  MAX_HISTOGRAM_BIN ; 
 size_t TSDB_DATA_TYPE_DOUBLE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_7__* calloc (int,int) ; 
 int /*<<< orphan*/  histogramCreateBin (TYPE_6__*,size_t,double) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_21__* tDataTypeDesc ; 
 TYPE_6__* tHistogramCreate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tLoserTreeAdjust (TYPE_5__*,size_t) ; 
 int /*<<< orphan*/  tLoserTreeDisplay (TYPE_5__*) ; 
 int /*<<< orphan*/  tSkipListCreateKey (size_t,double*,int /*<<< orphan*/ ) ; 
 TYPE_4__* tSkipListGetOne (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tSkipListPrint (TYPE_9__*,int) ; 
 TYPE_4__* tSkipListPut (TYPE_9__*,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tSkipListRemoveNode (TYPE_9__*,TYPE_4__*) ; 
 size_t vnodeHistobinarySearch (TYPE_8__*,int,double) ; 

int32_t tHistogramAdd(SHistogramInfo** pHisto, double val) {
  if (*pHisto == NULL) {
    *pHisto = tHistogramCreate(MAX_HISTOGRAM_BIN);
  }

#if defined(USE_ARRAYLIST)
  int32_t idx = vnodeHistobinarySearch((*pHisto)->elems, (*pHisto)->numOfEntries, val);
  assert(idx >= 0 && idx <= (*pHisto)->maxEntries);

  if ((*pHisto)->elems[idx].val == val && idx >= 0) {
    (*pHisto)->elems[idx].num += 1;

    if ((*pHisto)->numOfEntries == 0) {
      (*pHisto)->numOfEntries += 1;
    }
  } else { /* insert a new slot */
    if ((*pHisto)->numOfElems > 1 && idx < (*pHisto)->numOfEntries) {
      if (idx > 0) {
        assert((*pHisto)->elems[idx - 1].val <= val);
      }

      assert((*pHisto)->elems[idx].val > val);
    } else {
      assert((*pHisto)->elems[(*pHisto)->numOfEntries].val < val);
    }

    histogramCreateBin(*pHisto, idx, val);
  }
#else
  tSkipListKey key = tSkipListCreateKey(TSDB_DATA_TYPE_DOUBLE, &val, tDataTypeDesc[TSDB_DATA_TYPE_DOUBLE].nSize);
  SHistBin*    entry = calloc(1, sizeof(SHistBin));
  entry->val = val;

  tSkipListNode* pResNode = tSkipListPut((*pHisto)->pList, entry, &key, 0);

  SHistBin* pEntry1 = (SHistBin*)pResNode->pData;
  pEntry1->index = -1;

  tSkipListNode* pLast = NULL;

  if (pEntry1->num == 0) { /* it is a new node */
    (*pHisto)->numOfEntries += 1;
    pEntry1->num += 1;

    /* number of entries reaches the upper limitation */
    if (pResNode->pForward[0] != NULL) {
      /* we need to update the last updated slot in loser tree*/
      pEntry1->delta = ((SHistBin*)pResNode->pForward[0]->pData)->val - val;

      if ((*pHisto)->ordered) {
        int32_t         lastIndex = (*pHisto)->maxIndex;
        SLoserTreeInfo* pTree = (*pHisto)->pLoserTree;

        (*pHisto)->pLoserTree->pNode[lastIndex + pTree->numOfEntries].pData = pResNode;
        pEntry1->index = (*pHisto)->pLoserTree->pNode[lastIndex + pTree->numOfEntries].index;

        // update the loser tree
        if ((*pHisto)->ordered) {
          tLoserTreeAdjust(pTree, pEntry1->index + pTree->numOfEntries);
        }

        tSkipListKey kx =
            tSkipListCreateKey(TSDB_DATA_TYPE_DOUBLE, &(*pHisto)->max, tDataTypeDesc[TSDB_DATA_TYPE_DOUBLE].nSize);
        pLast = tSkipListGetOne((*pHisto)->pList, &kx);
      }
    } else {
      /* this node located at the last position of the skiplist, we do not
       * update the loser-tree */
      pEntry1->delta = DBL_MAX;
      pLast = pResNode;
    }

    if (pResNode->pBackward[0] != &(*pHisto)->pList->pHead) {
      SHistBin* pPrevEntry = (SHistBin*)pResNode->pBackward[0]->pData;
      pPrevEntry->delta = val - pPrevEntry->val;

      SLoserTreeInfo* pTree = (*pHisto)->pLoserTree;
      if ((*pHisto)->ordered) {
        tLoserTreeAdjust(pTree, pPrevEntry->index + pTree->numOfEntries);
        tLoserTreeDisplay(pTree);
      }
    }

    if ((*pHisto)->numOfEntries >= (*pHisto)->maxEntries + 1) {
      // set the right value for loser-tree
      assert((*pHisto)->pLoserTree != NULL);
      if (!(*pHisto)->ordered) {
        tSkipListPrint((*pHisto)->pList, 1);

        SLoserTreeInfo* pTree = (*pHisto)->pLoserTree;
        tSkipListNode*  pHead = (*pHisto)->pList->pHead.pForward[0];

        tSkipListNode* p1 = pHead;

        printf("\n");
        while (p1 != NULL) {
          printf("%f\t", ((SHistBin*)(p1->pData))->delta);
          p1 = p1->pForward[0];
        }
        printf("\n");

        /* last one in skiplist is ignored */
        for (int32_t i = pTree->numOfEntries; i < pTree->totalEntries; ++i) {
          pTree->pNode[i].pData = pHead;
          pTree->pNode[i].index = i - pTree->numOfEntries;
          SHistBin* pBin = (SHistBin*)pHead->pData;
          pBin->index = pTree->pNode[i].index;

          pHead = pHead->pForward[0];
        }

        pLast = pHead;

        for (int32_t i = 0; i < pTree->numOfEntries; ++i) {
          pTree->pNode[i].index = -1;
        }

        tLoserTreeDisplay(pTree);

        for (int32_t i = pTree->totalEntries - 1; i >= pTree->numOfEntries; i--) {
          tLoserTreeAdjust(pTree, i);
        }

        tLoserTreeDisplay(pTree);
        (*pHisto)->ordered = true;
      }

      printf("delta is:%lf\n", pEntry1->delta);

      tSkipListPrint((*pHisto)->pList, 1);

      /* the chosen node */
      tSkipListNode* pNode = (*pHisto)->pLoserTree->pNode[0].pData;
      SHistBin*      pEntry = (SHistBin*)pNode->pData;

      tSkipListNode* pNext = pNode->pForward[0];
      SHistBin*      pNextEntry = (SHistBin*)pNext->pData;
      assert(pNextEntry->val - pEntry->val == pEntry->delta);

      double newVal = (pEntry->val * pEntry->num + pNextEntry->val * pNextEntry->num) / (pEntry->num + pNextEntry->num);
      pEntry->val = newVal;
      pNode->key.dKey = newVal;
      pEntry->num = pEntry->num + pNextEntry->num;

      // update delta value in current node
      pEntry->delta = (pNextEntry->delta + pNextEntry->val) - pEntry->val;

      // reset delta value in the previous node
      SHistBin* pPrevEntry = (SHistBin*)pNode->pBackward[0]->pData;
      if (pPrevEntry) {
        pPrevEntry->delta = pEntry->val - pPrevEntry->val;
      }

      SLoserTreeInfo* pTree = (*pHisto)->pLoserTree;
      if (pNextEntry->index != -1) {
        (*pHisto)->maxIndex = pNextEntry->index;

        // set the last element in skiplist, of which delta is FLT_MAX;
        pTree->pNode[pNextEntry->index + pTree->numOfEntries].pData = pLast;
        ((SHistBin*)pLast->pData)->index = pNextEntry->index;
        int32_t f = pTree->pNode[pNextEntry->index + pTree->numOfEntries].index;
        printf("disappear index is:%d\n", f);
      }

      tLoserTreeAdjust(pTree, pEntry->index + pTree->numOfEntries);
      // remove the next node in skiplist
      tSkipListRemoveNode((*pHisto)->pList, pNext);
      tSkipListPrint((*pHisto)->pList, 1);

      tLoserTreeDisplay((*pHisto)->pLoserTree);
    } else {  // add to heap
      if (pResNode->pForward[0] != NULL) {
        pEntry1->delta = ((SHistBin*)pResNode->pForward[0]->pData)->val - val;
      } else {
        pEntry1->delta = DBL_MAX;
      }

      if (pResNode->pBackward[0] != &(*pHisto)->pList->pHead) {
        SHistBin* pPrevEntry = (SHistBin*)pResNode->pBackward[0]->pData;
        pEntry1->delta = val - pPrevEntry->val;
      }

      printf("delta is:%9lf\n", pEntry1->delta);
    }

  } else {
    SHistBin* pEntry = (SHistBin*)pResNode->pData;
    assert(pEntry->val == val);
    pEntry->num += 1;
  }

#endif
  if (val > (*pHisto)->max) {
    (*pHisto)->max = val;
  }

  if (val < (*pHisto)->min) {
    (*pHisto)->min = val;
  }

  (*pHisto)->numOfElems += 1;
  return 0;
}