#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ const num; } ;
typedef  TYPE_1__ tQueryResultset ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  doNestedLoopIntersect (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  doSortIntersect (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void queryResultIntersect(tQueryResultset* pFinalRes, tQueryResultset* pRes) {
  const int32_t NUM_OF_RES_THRESHOLD = 20;

  // for small result, use nested loop join
  if (pFinalRes->num <= NUM_OF_RES_THRESHOLD && pRes->num <= NUM_OF_RES_THRESHOLD) {
    doNestedLoopIntersect(pFinalRes, pRes);
  } else {  // for larger result, sort merge is employed
    doSortIntersect(pFinalRes, pRes);
  }
}