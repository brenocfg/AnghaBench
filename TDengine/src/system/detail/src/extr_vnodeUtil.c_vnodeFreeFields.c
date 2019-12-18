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
typedef  size_t int32_t ;
struct TYPE_3__ {size_t numOfBlocks; int /*<<< orphan*/ * pFields; } ;
typedef  TYPE_1__ SQuery ;

/* Variables and functions */
 int /*<<< orphan*/  tfree (int /*<<< orphan*/ ) ; 

void vnodeFreeFields(SQuery* pQuery) {
  if (pQuery == NULL || pQuery->pFields == NULL) {
    return;
  }

  for (int32_t i = 0; i < pQuery->numOfBlocks; ++i) {
    tfree(pQuery->pFields[i]);
  }

  /*
   * pQuery->pFields does not need to be released, it is allocated at the last part of pBlock
   * so free(pBlock) can release this memory at the same time.
   */
  pQuery->pFields = NULL;
  pQuery->numOfBlocks = 0;
}