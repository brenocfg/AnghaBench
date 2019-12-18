#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pExprs; } ;
struct TYPE_5__ {int /*<<< orphan*/ * tsBuf; TYPE_3__ colList; TYPE_3__ exprsInfo; int /*<<< orphan*/  fieldsInfo; int /*<<< orphan*/  tagCond; int /*<<< orphan*/  pDataBlocks; } ;
typedef  TYPE_1__ SSqlCmd ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsBufDestory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tscClearFieldInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tscColumnBaseInfoDestroy (TYPE_3__*) ; 
 int /*<<< orphan*/  tscDestroyBlockArrayList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscTagCondRelease (int /*<<< orphan*/ *) ; 

void tscFreeSqlCmdData(SSqlCmd* pCmd) {
  pCmd->pDataBlocks = tscDestroyBlockArrayList(pCmd->pDataBlocks);

  tscTagCondRelease(&pCmd->tagCond);
  tscClearFieldInfo(&pCmd->fieldsInfo);

  tfree(pCmd->exprsInfo.pExprs);
  memset(&pCmd->exprsInfo, 0, sizeof(pCmd->exprsInfo));

  tscColumnBaseInfoDestroy(&pCmd->colList);
  memset(&pCmd->colList, 0, sizeof(pCmd->colList));

  if (pCmd->tsBuf != NULL) {
    tsBufDestory(pCmd->tsBuf);
    pCmd->tsBuf = NULL;
  }
}