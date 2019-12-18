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
typedef  int uint8_t ;
struct TYPE_8__ {scalar_t__ code; scalar_t__ numOfRows; scalar_t__ row; } ;
struct TYPE_9__ {TYPE_1__ res; int /*<<< orphan*/  param; int /*<<< orphan*/  (* fp ) (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__) ;int /*<<< orphan*/  cmd; } ;
typedef  TYPE_1__ SSqlRes ;
typedef  TYPE_2__ SSqlObj ;
typedef  int /*<<< orphan*/  SSqlCmd ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__) ; 
 scalar_t__ tscLocalDoReduce (TYPE_2__*) ; 
 int /*<<< orphan*/  tscQueueAsyncRes (TYPE_2__*) ; 
 int /*<<< orphan*/  tscSetResultPointer (int /*<<< orphan*/ *,TYPE_1__*) ; 

int tscProcessRetrieveMetricRsp(SSqlObj *pSql) {
  SSqlRes *pRes = &pSql->res;
  SSqlCmd *pCmd = &pSql->cmd;

  pRes->code = tscLocalDoReduce(pSql);

  if (pRes->code == TSDB_CODE_SUCCESS && pRes->numOfRows > 0) {
    tscSetResultPointer(pCmd, pRes);
  }

  pRes->row = 0;

  uint8_t code = pSql->res.code;
  if (pSql->fp) {  // async retrieve metric data
    if (pSql->res.code == TSDB_CODE_SUCCESS) {
      (*pSql->fp)(pSql->param, pSql, pSql->res.numOfRows);
    } else {
      tscQueueAsyncRes(pSql);
    }
  }

  return code;
}