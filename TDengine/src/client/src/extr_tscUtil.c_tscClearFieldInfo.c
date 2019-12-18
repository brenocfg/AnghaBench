#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pVisibleCols; int /*<<< orphan*/  pFields; int /*<<< orphan*/  pOffset; } ;
typedef  TYPE_1__ SFieldInfo ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tfree (int /*<<< orphan*/ ) ; 

void tscClearFieldInfo(SFieldInfo* pFieldInfo) {
  if (pFieldInfo == NULL) {
    return;
  }

  tfree(pFieldInfo->pOffset);
  tfree(pFieldInfo->pFields);
  tfree(pFieldInfo->pVisibleCols);

  memset(pFieldInfo, 0, sizeof(SFieldInfo));
}