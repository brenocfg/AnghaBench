#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * pSql; } ;
typedef  int /*<<< orphan*/  TAOS_STMT ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_1__ STscStmt ;

/* Variables and functions */
 int /*<<< orphan*/  tscError (char*) ; 

TAOS_RES *taos_stmt_use_result(TAOS_STMT* stmt) {
  if (stmt == NULL) {
    tscError("statement is invalid.");
    return NULL;
  }

  STscStmt* pStmt = (STscStmt*)stmt;
  if (pStmt->pSql == NULL) {
    tscError("result has been used already.");
    return NULL;
  }

  TAOS_RES* result = pStmt->pSql;
  pStmt->pSql = NULL;
  return result;
}