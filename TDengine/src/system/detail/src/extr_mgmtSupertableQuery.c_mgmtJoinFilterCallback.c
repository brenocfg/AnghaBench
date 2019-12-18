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
struct TYPE_6__ {scalar_t__ pData; } ;
typedef  TYPE_1__ tSkipListNode ;
typedef  size_t int32_t ;
struct TYPE_8__ {size_t size; int /*<<< orphan*/ * val; int /*<<< orphan*/ * pTabObjs; int /*<<< orphan*/  qualSize; int /*<<< orphan*/ * qualMeterObj; int /*<<< orphan*/  type; int /*<<< orphan*/  colIndex; } ;
struct TYPE_7__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  STabObj ;
typedef  TYPE_2__ SSchema ;
typedef  TYPE_3__ SJoinSupporter ;

/* Variables and functions */
 size_t doCompare (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 char* mgmtMeterGetTag (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static bool mgmtJoinFilterCallback(tSkipListNode* pNode, void* param) {
  SJoinSupporter* pSupporter = (SJoinSupporter*)param;

  SSchema s = {0};
  char*   v = mgmtMeterGetTag((STabObj*)pNode->pData, pSupporter->colIndex, &s);

  for (int32_t i = 0; i < pSupporter->size; ++i) {
    int32_t ret = doCompare(v, pSupporter->val[i], pSupporter->type, s.bytes);
    if (ret == 0) {
      pSupporter->qualMeterObj[pSupporter->qualSize++] = pSupporter->pTabObjs[i];

      /*
       * Once a value is qualified according to the join condition, it is remove from the
       * candidate list, as well as its corresponding meter object.
       *
       * last one does not need to move forward
       */
      if (i < pSupporter->size - 1) {
        memmove(pSupporter->val[i], pSupporter->val[i + 1], pSupporter->size - (i + 1));
      }

      pSupporter->size -= 1;

      return true;
    }
  }

  return false;
}