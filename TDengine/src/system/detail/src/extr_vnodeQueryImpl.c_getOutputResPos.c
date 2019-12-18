#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ data; } ;
typedef  TYPE_2__ tFilePage ;
typedef  size_t int32_t ;
struct TYPE_8__ {int* offset; int numOfRowsPerPage; TYPE_1__* pCtx; } ;
struct TYPE_6__ {size_t outputBytes; } ;
typedef  TYPE_3__ SQueryRuntimeEnv ;

/* Variables and functions */
 size_t DEFAULT_INTERN_BUF_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static char *getOutputResPos(SQueryRuntimeEnv *pRuntimeEnv, tFilePage *pData, int32_t row, int32_t col) {
  // the output for each record should be less than the DEFAULT_INTERN_BUF_SIZE
  assert(pRuntimeEnv->pCtx[col].outputBytes <= DEFAULT_INTERN_BUF_SIZE);

  return (char *)pData->data + pRuntimeEnv->offset[col] * pRuntimeEnv->numOfRowsPerPage +
         pRuntimeEnv->pCtx[col].outputBytes * row;
}