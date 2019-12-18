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
struct TYPE_5__ {size_t num; scalar_t__* pRes; } ;
typedef  TYPE_1__ tQueryResultset ;
typedef  size_t int32_t ;

/* Variables and functions */
 size_t POINTER_BYTES ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  qsort (scalar_t__*,size_t,size_t,int /*<<< orphan*/ ) ; 
 void* realloc (scalar_t__*,size_t) ; 
 int /*<<< orphan*/  tQueryResultClean (TYPE_1__*) ; 
 int /*<<< orphan*/  tabObjPointerComparator ; 

__attribute__((used)) static void queryResultUnion(tQueryResultset* pFinalRes, tQueryResultset* pRes) {
  if (pRes->num == 0) {
    tQueryResultClean(pRes);
    return;
  }

  int32_t total = pFinalRes->num + pRes->num;
  void*   tmp = realloc(pFinalRes->pRes, total * POINTER_BYTES);
  if (tmp == NULL) {
    return;
  }
  pFinalRes->pRes = tmp;

  memcpy(&pFinalRes->pRes[pFinalRes->num], pRes->pRes, POINTER_BYTES * pRes->num);
  qsort(pFinalRes->pRes, total, POINTER_BYTES, tabObjPointerComparator);

  int32_t num = 1;
  for (int32_t i = 1; i < total; ++i) {
    if (pFinalRes->pRes[i] != pFinalRes->pRes[i - 1]) {
      pFinalRes->pRes[num++] = pFinalRes->pRes[i];
    }
  }

  if (num < total) {
    memset(&pFinalRes->pRes[num], 0, POINTER_BYTES * (total - num));
  }

  pFinalRes->num = num;

  tQueryResultClean(pRes);
}