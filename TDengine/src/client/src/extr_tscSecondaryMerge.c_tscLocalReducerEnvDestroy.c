#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tOrderDescriptor ;
typedef  int /*<<< orphan*/  tExtMemBuffer ;
typedef  int /*<<< orphan*/  tColModel ;
typedef  size_t int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  tColModelDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tExtMemBufferDestroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  tOrderDescDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tfree (int /*<<< orphan*/ **) ; 

void tscLocalReducerEnvDestroy(tExtMemBuffer **pMemBuffer, tOrderDescriptor *pDesc, tColModel *pFinalModel,
                               int32_t numOfVnodes) {
  tColModelDestroy(pFinalModel);
  tOrderDescDestroy(pDesc);
  for (int32_t i = 0; i < numOfVnodes; ++i) {
    tExtMemBufferDestroy(&pMemBuffer[i]);
  }

  tfree(pMemBuffer);
}