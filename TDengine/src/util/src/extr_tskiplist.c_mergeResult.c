#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__** pForward; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ tSkipListNode ;
typedef  int /*<<< orphan*/  tSkipListKey ;
typedef  size_t int32_t ;
typedef  size_t (* __compar_fn_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ;

/* Variables and functions */

int32_t mergeResult(const tSkipListKey *pKey, int32_t numOfKey, tSkipListNode ***pRes, __compar_fn_t comparator,
                    tSkipListNode *pNode) {
  int32_t i = 0, j = 0;
  // merge two sorted arrays in O(n) time
  while (i < numOfKey && pNode != NULL) {
    int32_t ret = comparator(&pNode->key, &pKey[i]);
    if (ret < 0) {
      (*pRes)[j++] = pNode;
      pNode = pNode->pForward[0];
    } else if (ret == 0) {
      pNode = pNode->pForward[0];
    } else {  // pNode->key > pkey[i]
      i++;
    }
  }

  while (pNode != NULL) {
    (*pRes)[j++] = pNode;
    pNode = pNode->pForward[0];
  }
  return j;
}