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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/ * data; scalar_t__ pRsp; int /*<<< orphan*/  qhandle; } ;
struct TYPE_6__ {TYPE_1__ res; } ;
typedef  TYPE_1__ SSqlRes ;
typedef  TYPE_2__ SSqlObj ;

/* Variables and functions */
 int /*<<< orphan*/  tscResetForNextRetrieve (TYPE_1__*) ; 

int tscProcessQueryRsp(SSqlObj *pSql) {
  SSqlRes *pRes = &pSql->res;

  pRes->qhandle = *((uint64_t *)pRes->pRsp);
  pRes->data = NULL;
  tscResetForNextRetrieve(pRes);
  return 0;
}