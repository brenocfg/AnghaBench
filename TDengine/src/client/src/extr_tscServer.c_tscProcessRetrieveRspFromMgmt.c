#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  data; int /*<<< orphan*/  numOfRows; } ;
struct TYPE_8__ {scalar_t__ numOfRows; scalar_t__ row; int /*<<< orphan*/  data; int /*<<< orphan*/  precision; scalar_t__ pRsp; } ;
struct TYPE_9__ {int /*<<< orphan*/ * thandle; int /*<<< orphan*/  vnode; int /*<<< orphan*/  ip; TYPE_1__* pTscObj; int /*<<< orphan*/  cmd; TYPE_2__ res; } ;
struct TYPE_7__ {int /*<<< orphan*/  user; } ;
typedef  TYPE_1__ STscObj ;
typedef  TYPE_2__ SSqlRes ;
typedef  TYPE_3__ SSqlObj ;
typedef  int /*<<< orphan*/  SSqlCmd ;
typedef  TYPE_4__ SRetrieveMeterRsp ;

/* Variables and functions */
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosAddConnIntoCache (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscConnCache ; 
 int /*<<< orphan*/  tscSetResultPointer (int /*<<< orphan*/ *,TYPE_2__*) ; 

int tscProcessRetrieveRspFromMgmt(SSqlObj *pSql) {
  SSqlRes *pRes = &pSql->res;
  SSqlCmd *pCmd = &pSql->cmd;
  STscObj *pObj = pSql->pTscObj;

  SRetrieveMeterRsp *pRetrieve = (SRetrieveMeterRsp *)(pRes->pRsp);
  pRes->numOfRows = htonl(pRetrieve->numOfRows);
  pRes->precision = htons(pRes->precision);

  pRes->data = pRetrieve->data;

  tscSetResultPointer(pCmd, pRes);

  if (pRes->numOfRows == 0) {
    taosAddConnIntoCache(tscConnCache, pSql->thandle, pSql->ip, pSql->vnode, pObj->user);
    pSql->thandle = NULL;
  }

  pRes->row = 0;
  return 0;
}