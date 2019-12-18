#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  data; int /*<<< orphan*/  numOfRows; } ;
struct TYPE_6__ {scalar_t__ row; int /*<<< orphan*/  data; int /*<<< orphan*/  numOfRows; scalar_t__ pRsp; } ;
struct TYPE_7__ {int /*<<< orphan*/  cmd; TYPE_1__ res; } ;
typedef  TYPE_1__ SSqlRes ;
typedef  TYPE_2__ SSqlObj ;
typedef  int /*<<< orphan*/  SSqlCmd ;
typedef  TYPE_3__ SRetrieveMeterRsp ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscSetResultPointer (int /*<<< orphan*/ *,TYPE_1__*) ; 

int tscProcessRetrieveRspFromLocal(SSqlObj *pSql) {
  SSqlRes *          pRes = &pSql->res;
  SSqlCmd *          pCmd = &pSql->cmd;
  SRetrieveMeterRsp *pRetrieve = (SRetrieveMeterRsp *)pRes->pRsp;

  pRes->numOfRows = htonl(pRetrieve->numOfRows);
  pRes->data = pRetrieve->data;

  tscSetResultPointer(pCmd, pRes);
  pRes->row = 0;
  return 0;
}