#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSkipListNode ;
typedef  size_t int32_t ;
struct TYPE_3__ {size_t len; int /*<<< orphan*/ ** pData; } ;
typedef  TYPE_1__ MultipleQueryResult ;

/* Variables and functions */
 size_t POINTER_BYTES ; 
 int /*<<< orphan*/ ** malloc (size_t) ; 

__attribute__((used)) static int32_t mergeQueryResult(MultipleQueryResult *pResults, int32_t numOfResSet, tSkipListNode ***pRes) {
  int32_t total = 0;
  for (int32_t i = 0; i < numOfResSet; ++i) {
    total += pResults[i].len;
  }

  (*pRes) = malloc(POINTER_BYTES * total);
  int32_t idx = 0;

  for (int32_t i = 0; i < numOfResSet; ++i) {
    MultipleQueryResult *pOneResult = &pResults[i];
    for (int32_t j = 0; j < pOneResult->len; ++j) {
      (*pRes)[idx++] = pOneResult->pData[j];
    }
  }

  return total;
}