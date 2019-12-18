#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  code; } ;
struct TYPE_10__ {TYPE_1__ res; } ;
struct TYPE_9__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  pTimer; TYPE_3__* pSql; int /*<<< orphan*/ * signature; } ;
typedef  TYPE_2__ STscObj ;
typedef  TYPE_3__ SSqlObj ;

/* Variables and functions */
 int /*<<< orphan*/  globalCode ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taosTmrStopA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tfree (TYPE_2__*) ; 
 int /*<<< orphan*/  tscFreeSqlObj (TYPE_3__*) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_2__*) ; 

void tscCloseTscObj(STscObj* pObj) {
  pObj->signature = NULL;
  SSqlObj* pSql = pObj->pSql;
  globalCode = pSql->res.code;

  taosTmrStopA(&(pObj->pTimer));
  tscFreeSqlObj(pSql);

  pthread_mutex_destroy(&pObj->mutex);
  tscTrace("%p DB connection is closed", pObj);
  tfree(pObj);
}