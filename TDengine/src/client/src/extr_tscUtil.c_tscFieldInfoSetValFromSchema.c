#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_8__ {scalar_t__ numOfOutputCols; int /*<<< orphan*/ * pFields; } ;
struct TYPE_7__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  TAOS_FIELD ;
typedef  TYPE_1__ SSchema ;
typedef  TYPE_2__ SFieldInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ensureSpace (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  evic (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  setValueImpl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void tscFieldInfoSetValFromSchema(SFieldInfo* pFieldInfo, int32_t index, SSchema* pSchema) {
  ensureSpace(pFieldInfo, pFieldInfo->numOfOutputCols + 1);
  evic(pFieldInfo, index);

  TAOS_FIELD* pField = &pFieldInfo->pFields[index];
  setValueImpl(pField, pSchema->type, pSchema->name, pSchema->bytes);
  pFieldInfo->numOfOutputCols++;
}