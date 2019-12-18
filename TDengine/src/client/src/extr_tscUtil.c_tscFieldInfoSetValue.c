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
typedef  int /*<<< orphan*/  int8_t ;
typedef  size_t int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_5__ {int* pVisibleCols; scalar_t__ numOfOutputCols; int /*<<< orphan*/ * pFields; } ;
typedef  int /*<<< orphan*/  TAOS_FIELD ;
typedef  TYPE_1__ SFieldInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ensureSpace (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  evic (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  setValueImpl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void tscFieldInfoSetValue(SFieldInfo* pFieldInfo, int32_t index, int8_t type, char* name, int16_t bytes) {
  ensureSpace(pFieldInfo, pFieldInfo->numOfOutputCols + 1);
  evic(pFieldInfo, index);

  TAOS_FIELD* pField = &pFieldInfo->pFields[index];
  setValueImpl(pField, type, name, bytes);

  pFieldInfo->pVisibleCols[index] = true;
  pFieldInfo->numOfOutputCols++;
}