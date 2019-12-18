#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ (* __block_search_fn_t ) (char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ;
struct TYPE_5__ {int /*<<< orphan*/  order; } ;
struct TYPE_6__ {scalar_t__ ekey; scalar_t__ pos; TYPE_1__ order; } ;
typedef  TYPE_2__ SQuery ;

/* Variables and functions */
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int32_t getForwardStepsInBlock(int32_t numOfPoints, __block_search_fn_t searchFn, SQuery *pQuery,
                                      int64_t *pData) {
  int32_t endPos = searchFn((char *)pData, numOfPoints, pQuery->ekey, pQuery->order.order);
  int32_t forwardStep = 0;

  if (endPos >= 0) {
    forwardStep = QUERY_IS_ASC_QUERY(pQuery) ? (endPos - pQuery->pos) : (pQuery->pos - endPos);
    assert(forwardStep >= 0);

    // endPos data is equalled to the key so, we do need to read the element in endPos
    if (pData[endPos] == pQuery->ekey) {
      forwardStep += 1;
    }
  }
  return forwardStep;
}