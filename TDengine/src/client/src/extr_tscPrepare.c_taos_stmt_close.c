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
typedef  scalar_t__ uint16_t ;
struct TYPE_6__ {scalar_t__ numParams; TYPE_1__* sql; TYPE_1__* parts; TYPE_1__* params; } ;
struct TYPE_5__ {int /*<<< orphan*/  pSql; TYPE_2__ normal; int /*<<< orphan*/  isInsert; } ;
typedef  int /*<<< orphan*/  TAOS_STMT ;
typedef  TYPE_1__ STscStmt ;
typedef  TYPE_2__ SNormalStmt ;

/* Variables and functions */
 int TSDB_CODE_SUCCESS ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  tVariantDestroy (TYPE_1__*) ; 
 int /*<<< orphan*/  tscFreeSqlObj (int /*<<< orphan*/ ) ; 

int taos_stmt_close(TAOS_STMT* stmt) {
  STscStmt* pStmt = (STscStmt*)stmt;
  if (!pStmt->isInsert) {
    SNormalStmt* normal = &pStmt->normal;
    if (normal->params != NULL) {
      for (uint16_t i = 0; i < normal->numParams; i++) {
        tVariantDestroy(normal->params + i);
      }
      free(normal->params);
    }
    free(normal->parts);
    free(normal->sql);
  }

  tscFreeSqlObj(pStmt->pSql);
  free(pStmt);
  return TSDB_CODE_SUCCESS;
}