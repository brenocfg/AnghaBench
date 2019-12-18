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
typedef  size_t int32_t ;
struct TYPE_8__ {scalar_t__ resBytes; } ;
struct TYPE_7__ {scalar_t__ numOfOutputCols; scalar_t__* pOffset; } ;
struct TYPE_6__ {TYPE_2__ fieldsInfo; } ;
typedef  TYPE_1__ SSqlCmd ;
typedef  TYPE_2__ SFieldInfo ;

/* Variables and functions */
 TYPE_3__* tscSqlExprGet (TYPE_1__*,size_t) ; 

void tscFieldInfoUpdateOffset(SSqlCmd* pCmd) {
  SFieldInfo* pFieldInfo = &pCmd->fieldsInfo;
  if (pFieldInfo->numOfOutputCols == 0) {
    return;
  }

  pFieldInfo->pOffset[0] = 0;

  /*
   * the retTypeLen is used to store the intermediate result length
   * for potential secondary merge exists
   */
  for (int32_t i = 1; i < pFieldInfo->numOfOutputCols; ++i) {
    pFieldInfo->pOffset[i] = pFieldInfo->pOffset[i - 1] + tscSqlExprGet(pCmd, i - 1)->resBytes;
  }
}