#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ isInsert; } ;
typedef  int /*<<< orphan*/  TAOS_STMT ;
typedef  int /*<<< orphan*/  TAOS_BIND ;
typedef  TYPE_1__ STscStmt ;

/* Variables and functions */
 int insertStmtBindParam (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int normalStmtBindParam (TYPE_1__*,int /*<<< orphan*/ *) ; 

int taos_stmt_bind_param(TAOS_STMT* stmt, TAOS_BIND* bind) {
  STscStmt* pStmt = (STscStmt*)stmt;
  if (pStmt->isInsert) {
    return insertStmtBindParam(pStmt, bind);
  }
  return normalStmtBindParam(pStmt, bind);
}