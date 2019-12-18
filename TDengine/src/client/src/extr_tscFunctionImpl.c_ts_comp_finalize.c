#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  aOutputBuf; } ;
struct TYPE_13__ {TYPE_1__* interResultBuf; } ;
struct TYPE_12__ {int /*<<< orphan*/  path; } ;
struct TYPE_11__ {TYPE_2__* pTSBuf; } ;
typedef  TYPE_1__ STSCompInfo ;
typedef  TYPE_2__ STSBuf ;
typedef  TYPE_3__ SResultInfo ;
typedef  TYPE_4__ SQLFunctionCtx ;

/* Variables and functions */
 TYPE_3__* GET_RES_INFO (TYPE_4__*) ; 
 int /*<<< orphan*/  resetResultInfo (TYPE_3__*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsBufDestory (TYPE_2__*) ; 
 int /*<<< orphan*/  tsBufFlush (TYPE_2__*) ; 

__attribute__((used)) static void ts_comp_finalize(SQLFunctionCtx *pCtx) {
  SResultInfo *pResInfo = GET_RES_INFO(pCtx);

  STSCompInfo *pInfo = pResInfo->interResultBuf;
  STSBuf *     pTSbuf = pInfo->pTSBuf;

  tsBufFlush(pTSbuf);
  strcpy(pCtx->aOutputBuf, pTSbuf->path);

  tsBufDestory(pTSbuf);
  resetResultInfo(GET_RES_INFO(pCtx));
}