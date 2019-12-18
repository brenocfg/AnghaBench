#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* pTscObj; struct TYPE_9__* signature; int /*<<< orphan*/  emptyRspSem; int /*<<< orphan*/  rspSem; } ;
struct TYPE_8__ {struct TYPE_8__* signature; } ;
struct TYPE_7__ {TYPE_4__* pSql; } ;
typedef  TYPE_1__ TAOS_STMT ;
typedef  int /*<<< orphan*/  TAOS ;
typedef  TYPE_1__ STscStmt ;
typedef  TYPE_3__ STscObj ;
typedef  TYPE_4__ SSqlObj ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_CODE_CLI_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  TSDB_CODE_DISCONNECTED ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  globalCode ; 
 int /*<<< orphan*/  tscError (char*) ; 
 int /*<<< orphan*/  tsem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

TAOS_STMT* taos_stmt_init(TAOS* taos) {
  STscObj* pObj = (STscObj*)taos;
  if (pObj == NULL || pObj->signature != pObj) {
    globalCode = TSDB_CODE_DISCONNECTED;
    tscError("connection disconnected");
    return NULL;
  }

  STscStmt* pStmt = calloc(1, sizeof(STscStmt));
  if (pStmt == NULL) {
    globalCode = TSDB_CODE_CLI_OUT_OF_MEMORY;
    tscError("failed to allocate memory for statement");
    return NULL;
  }

  SSqlObj* pSql = calloc(1, sizeof(SSqlObj));
  if (pSql == NULL) {
    free(pStmt);
    globalCode = TSDB_CODE_CLI_OUT_OF_MEMORY;
    tscError("failed to allocate memory for statement");
    return NULL;
  }

  tsem_init(&pSql->rspSem, 0, 0);
  tsem_init(&pSql->emptyRspSem, 0, 1);
  pSql->signature = pSql;
  pSql->pTscObj = pObj;

  pStmt->pSql = pSql;
  return pStmt;
}