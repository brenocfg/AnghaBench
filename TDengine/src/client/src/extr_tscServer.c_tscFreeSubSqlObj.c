#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  queryMutex; struct TYPE_11__* localBuffer; } ;
struct TYPE_9__ {scalar_t__ code; } ;
struct TYPE_10__ {TYPE_1__ res; } ;
typedef  TYPE_2__ SSqlObj ;
typedef  TYPE_3__ SRetrieveSupport ;

/* Variables and functions */
 scalar_t__ TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taos_free_result (TYPE_2__*) ; 
 int /*<<< orphan*/  tfree (TYPE_3__*) ; 
 int /*<<< orphan*/  tscTrace (char*,TYPE_2__*) ; 

__attribute__((used)) static void tscFreeSubSqlObj(SRetrieveSupport *trsupport, SSqlObj *pSql) {
  tscTrace("%p start to free subquery result", pSql);

  if (pSql->res.code == TSDB_CODE_SUCCESS) {
    taos_free_result(pSql);
  }

  tfree(trsupport->localBuffer);

  pthread_mutex_unlock(&trsupport->queryMutex);
  pthread_mutex_destroy(&trsupport->queryMutex);

  tfree(trsupport);
}