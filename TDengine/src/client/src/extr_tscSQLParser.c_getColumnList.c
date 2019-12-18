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
typedef  int int32_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_5__ {int num; TYPE_1__* ids; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int columnIndex; scalar_t__ tableIndex; } ;
typedef  TYPE_2__ SColumnList ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static SColumnList getColumnList(int32_t num, int16_t tableIndex, int32_t columnIndex) {
  assert(num == 1 && columnIndex >= -1 && tableIndex >= 0);

  SColumnList columnList = {0};
  columnList.num = num;

  int32_t index = num - 1;
  columnList.ids[index].tableIndex = tableIndex;
  columnList.ids[index].columnIndex = columnIndex;

  return columnList;
}