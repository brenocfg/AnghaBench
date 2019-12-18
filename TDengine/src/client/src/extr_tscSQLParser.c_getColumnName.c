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
struct TYPE_7__ {TYPE_2__* pNode; int /*<<< orphan*/ * aliasName; } ;
typedef  TYPE_3__ tSQLExprItem ;
typedef  scalar_t__ int32_t ;
struct TYPE_5__ {scalar_t__ n; int /*<<< orphan*/ * z; } ;
struct TYPE_6__ {TYPE_1__ operand; } ;

/* Variables and functions */
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ *,scalar_t__) ; 

void getColumnName(tSQLExprItem* pItem, char* resultFieldName, int32_t nameLength) {
  if (pItem->aliasName != NULL) {
    strncpy(resultFieldName, pItem->aliasName, nameLength);
  } else {
    int32_t len = (pItem->pNode->operand.n < nameLength) ? pItem->pNode->operand.n : nameLength;
    strncpy(resultFieldName, pItem->pNode->operand.z, len);
  }
}