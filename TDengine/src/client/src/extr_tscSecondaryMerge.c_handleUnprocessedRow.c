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
typedef  int /*<<< orphan*/  tFilePage ;
struct TYPE_5__ {int hasUnprocessedRow; } ;
typedef  int /*<<< orphan*/  SSqlCmd ;
typedef  TYPE_1__ SLocalReducer ;

/* Variables and functions */
 int /*<<< orphan*/  doExecuteSecondaryMerge (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  savePreviousRow (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handleUnprocessedRow(SSqlCmd* pCmd, SLocalReducer *pLocalReducer, tFilePage *tmpBuffer) {
  if (pLocalReducer->hasUnprocessedRow) {
    pLocalReducer->hasUnprocessedRow = false;
    doExecuteSecondaryMerge(pCmd, pLocalReducer, true);
    savePreviousRow(pLocalReducer, tmpBuffer);
  }
}