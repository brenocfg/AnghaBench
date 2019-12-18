#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_4__ {size_t numOfOutputCols; int /*<<< orphan*/ * pOffset; } ;
struct TYPE_5__ {TYPE_1__ fieldsInfo; } ;
typedef  TYPE_2__ SSqlCmd ;

/* Variables and functions */

int16_t tscFieldInfoGetOffset(SSqlCmd* pCmd, int32_t index) {
  if (index >= pCmd->fieldsInfo.numOfOutputCols) {
    return 0;
  }

  return pCmd->fieldsInfo.pOffset[index];
}