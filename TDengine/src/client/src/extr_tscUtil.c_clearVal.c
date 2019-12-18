#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int tableIndex; int columnIndex; } ;
struct TYPE_6__ {TYPE_1__ colIndex; } ;
typedef  TYPE_2__ SColumnBase ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clearVal(SColumnBase* pBase) {
  memset(pBase, 0, sizeof(SColumnBase));

  pBase->colIndex.tableIndex = -2;
  pBase->colIndex.columnIndex = -2;
}