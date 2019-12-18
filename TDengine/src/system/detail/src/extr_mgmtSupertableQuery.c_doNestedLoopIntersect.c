#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void** pRes; size_t num; } ;
typedef  TYPE_1__ tQueryResultset ;
typedef  size_t int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tQueryResultClean (TYPE_1__*) ; 

__attribute__((used)) static tQueryResultset* doNestedLoopIntersect(tQueryResultset* pRes1, tQueryResultset* pRes2) {
  int32_t num = 0;
  void**  pResult = pRes1->pRes;

  for (int32_t i = 0; i < pRes1->num; ++i) {
    for (int32_t j = 0; j < pRes2->num; ++j) {
      if (pRes1->pRes[i] == pRes2->pRes[j]) {
        pResult[num++] = pRes1->pRes[i];
        break;
      }
    }
  }

  tQueryResultClean(pRes2);

  memset(pRes1->pRes + num, 0, sizeof(void*) * (pRes1->num - num));
  pRes1->num = num;

  return pRes1;
}