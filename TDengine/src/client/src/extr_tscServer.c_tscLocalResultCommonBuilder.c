#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_8__ {scalar_t__ code; int rspType; int /*<<< orphan*/  numOfRows; scalar_t__ row; } ;
struct TYPE_9__ {TYPE_1__ res; int /*<<< orphan*/  param; int /*<<< orphan*/  (* fp ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  cmd; } ;
typedef  TYPE_1__ SSqlRes ;
typedef  TYPE_2__ SSqlObj ;
typedef  int /*<<< orphan*/  SSqlCmd ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscQueueAsyncRes (TYPE_2__*) ; 
 int /*<<< orphan*/  tscResetForNextRetrieve (TYPE_1__*) ; 
 int /*<<< orphan*/  tscSetResultPointer (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int tscLocalResultCommonBuilder(SSqlObj *pSql, int32_t numOfRes) {
  SSqlRes *pRes = &pSql->res;
  SSqlCmd *pCmd = &pSql->cmd;

  pRes->code = TSDB_CODE_SUCCESS;

  if (pRes->rspType == 0) {
    pRes->numOfRows = numOfRes;
    pRes->row = 0;
    pRes->rspType = 1;

    tscSetResultPointer(pCmd, pRes);
    pRes->row = 0;

  } else {
    tscResetForNextRetrieve(pRes);
  }

  uint8_t code = pSql->res.code;
  if (pSql->fp) {
    if (code == TSDB_CODE_SUCCESS) {
      (*pSql->fp)(pSql->param, pSql, pSql->res.numOfRows);
    } else {
      tscQueueAsyncRes(pSql);
    }
  }

  return code;
}