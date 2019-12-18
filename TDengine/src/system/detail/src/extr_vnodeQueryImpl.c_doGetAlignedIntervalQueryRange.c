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
struct TYPE_5__ {scalar_t__ skey; scalar_t__ lastKey; scalar_t__ ekey; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_1__ SQuery ;

/* Variables and functions */
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  doGetAlignedIntervalQueryRangeImpl (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static void doGetAlignedIntervalQueryRange(SQuery *pQuery, TSKEY key, TSKEY skey, TSKEY ekey) {
  TSKEY skey1, ekey1;

  TSKEY skey2 = (skey < ekey) ? skey : ekey;
  TSKEY ekey2 = (skey < ekey) ? ekey : skey;

  doGetAlignedIntervalQueryRangeImpl(pQuery, key, skey2, ekey2, &skey1, &ekey1);

  if (QUERY_IS_ASC_QUERY(pQuery)) {
    pQuery->skey = skey1;
    pQuery->ekey = ekey1;
    assert(pQuery->skey <= pQuery->ekey);
  } else {
    pQuery->skey = ekey1;
    pQuery->ekey = skey1;
    assert(pQuery->skey >= pQuery->ekey);
  }

  pQuery->lastKey = pQuery->skey;
}