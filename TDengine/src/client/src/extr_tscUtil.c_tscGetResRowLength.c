#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_7__ {int numOfOutputCols; TYPE_1__* pFields; scalar_t__* pOffset; } ;
struct TYPE_6__ {TYPE_3__ fieldsInfo; } ;
struct TYPE_5__ {scalar_t__ bytes; } ;
typedef  TYPE_2__ SSqlCmd ;
typedef  TYPE_3__ SFieldInfo ;

/* Variables and functions */

int32_t tscGetResRowLength(SSqlCmd* pCmd) {
  SFieldInfo* pFieldInfo = &pCmd->fieldsInfo;
  if (pFieldInfo->numOfOutputCols <= 0) {
    return 0;
  }

  return pFieldInfo->pOffset[pFieldInfo->numOfOutputCols - 1] +
         pFieldInfo->pFields[pFieldInfo->numOfOutputCols - 1].bytes;
}